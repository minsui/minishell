/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkim2 <mkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 14:43:37 by mkim2             #+#    #+#             */
/*   Updated: 2026/07/24 17:14:39 by mkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/wait.h>

static int	is_delimiter(char *line, char *delimiter)
{
	return (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1)
		&& ft_strlen(line) == ft_strlen(delimiter));
}

static void	read_heredoc(int wfd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr("minishell: warning: here-document "
				"delimited by end-of-file\n", 2);
			break ;
		}
		if (is_delimiter(line, delimiter))
		{
			free(line);
			break ;
		}
		write(wfd, line, ft_strlen(line));
		write(wfd, "\n", 1);
		free(line);
	}
}

static void	heredoc_child(int *fd, char *delimiter)
{
	signal(SIGINT, SIG_DFL);
	close(fd[0]);
	read_heredoc(fd[1], delimiter);
	close(fd[1]);
	exit(0);
}

int	fill_heredoc_pipe(char *delimiter)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		heredoc_child(fd, delimiter);
	signal(SIGINT, SIG_IGN);
	close(fd[1]);
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFSIGNALED(status))
	{
		g_signal = SIGINT;
		write(1, "\n", 1);
		close(fd[0]);
		return (-1);
	}
	return (fd[0]);
}
