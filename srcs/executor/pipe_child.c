/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkim2 <mkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 15:25:05 by mkim2             #+#    #+#             */
/*   Updated: 2026/07/23 20:18:38 by mkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	connect_pipes(t_cmd *cmd, int prev_fd, int *fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
}

static void	run_external(t_cmd *cmd, char **envp)
{
	char	*path;

	path = get_path(cmd->argv[0], envp);
	if (!path)
	{
		printf("%s: command not found\n", cmd->argv[0]);
		exit(127);
	}
	execve(path, cmd->argv, envp);
	perror("execve");
	free(path);
	exit(126);
}

void	exec_child(t_cmd *cmd, int prev_fd, int *fd, t_shell *shell)
{
	int	ret;

	connect_pipes(cmd, prev_fd, fd);
	setup_child_signals();
	if (handle_redirection(cmd) == -1)
		exit(1);
	if (is_builtin(cmd->argv[0]))
	{
		ret = execute_builtin(cmd, shell);
		exit(ret);
	}
	run_external(cmd, shell->env);
}
