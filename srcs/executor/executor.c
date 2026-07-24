/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkim2 <mkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 15:28:21 by mkim2             #+#    #+#             */
/*   Updated: 2026/07/24 17:10:09 by mkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/wait.h>

static void	wait_and_store_status(pid_t pid, t_shell *shell)
{
	int	status;

	waitpid(pid, &status, 0);
	setup_signals();
	store_status(status, shell);
}

void	execute_command(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;

	if (prepare_heredocs(cmd, shell) == -1)
		return ;
	if (!cmd->argv || !cmd->argv[0] || is_builtin(cmd->argv[0]))
	{
		run_builtin_in_parent(cmd, shell);
		return ;
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		shell->exit_status = 1;
		setup_signals();
		return ;
	}  
	if (pid == 0)
		child_process(cmd, shell);
	wait_and_store_status(pid, shell);
}

void	execute(t_cmd *cmds, t_shell *shell)
{
	if (!cmds)
		return ;
	if (cmds->next)
		execute_pipeline(cmds, shell);
	else
		execute_command(cmds, shell);
	close_heredocs(cmds);
}
