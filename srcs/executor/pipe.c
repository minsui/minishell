/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkim2 <mkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 15:07:10 by mkim2             #+#    #+#             */
/*   Updated: 2026/07/24 17:10:47 by mkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/wait.h>

static void	wait_children(pid_t last_pid, int count, t_shell *shell)
{
	int		status;
	int		i;
	pid_t	pid;

	i = 0;
	while (i < count)
	{
		pid = wait(&status);
		if (pid == last_pid)
			store_status(status, shell);
		i++;
	}
}

static pid_t	fork_one_cmd(t_cmd *cmd, int *prev_fd, t_shell *shell)
{
	int		fd[2];
	pid_t	pid;

	if (cmd->next && pipe(fd) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
		perror("minishell: fork");
	if (pid == 0)
		exec_child(cmd, *prev_fd, fd, shell);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
	return (pid);
}

void	execute_pipeline(t_cmd *cmds, t_shell *shell)
{
	int		prev_fd;
	int		count;
	pid_t	last_pid;

	if (prepare_heredocs(cmds, shell) == -1)
		return ;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	prev_fd = -1;
	count = 0;
	last_pid = -1;
	while (cmds)
	{
		last_pid = fork_one_cmd(cmds, &prev_fd, shell);
		if (last_pid != -1)
			count++;
		cmds = cmds->next;
		
	}
	wait_children(last_pid, count, shell);
	setup_signals();
}
