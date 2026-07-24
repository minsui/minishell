/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkim2 <mkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 15:58:02 by mkim2             #+#    #+#             */
/*   Updated: 2026/07/24 17:20:55 by mkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/wait.h>

static void	save_std_fds(int *saved_in, int *saved_out)
{
	*saved_in = dup(STDIN_FILENO);
	*saved_out = dup(STDOUT_FILENO);
}

static void	restore_std_fds(int saved_in, int saved_out)
{
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}

void	run_builtin_in_parent(t_cmd *cmd, t_shell *shell)
{
	int	saved_in;
	int	saved_out;

	save_std_fds(&saved_in, &saved_out);
	if (handle_redirection(cmd) == -1)
		shell->exit_status = 1;
	else if (cmd->argv && cmd->argv[0])
		shell->exit_status = execute_builtin(cmd, shell);
	else
		shell->exit_status = 0;
	restore_std_fds(saved_in, saved_out);
}

void	child_process(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	setup_child_signals();
	if (handle_redirection(cmd) == -1)
		exit(1);
	if (is_builtin(cmd->argv[0]))
		exit(execute_builtin(cmd, shell));
	path = get_path(cmd->argv[0], shell->env);
	if (!path)
	{
		ft_putstr("minishell: ", 2);
		ft_putstr(cmd->argv[0], 2);
		ft_putstr(": command not found\n", 2);
		exit(127);
	}
	execve(path, cmd->argv, shell->env);
	perror(cmd->argv[0]);
	free(path);
	exit(126);
}

void	store_status(int status, t_shell *shell)
{
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		shell->exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			write(2, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
	}
}
