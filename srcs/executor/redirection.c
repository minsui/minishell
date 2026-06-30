#include "../../includes/minishell.h"
#include <fcntl.h>

static void	handle_input(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->infile, O_RDONLY);
	if (fd < 0)
	{
		perror(cmd->infile);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	handle_output(t_cmd *cmd)
{
	int	fd;

	if (cmd->append)
		fd = open(cmd->outfile,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(cmd->outfile,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(cmd->outfile);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_redirection(t_cmd *cmd)
{
	if (cmd->heredoc)
	{
		handle_heredoc(cmd);
		return ;
	}
	if (cmd->infile)
		handle_input(cmd);
	if (cmd->outfile)
		handle_output(cmd);
}
