#include "../../includes/minishell.h"
#include <fcntl.h>

static void	write_heredoc(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strncmp(line, delimiter,
				ft_strlen(delimiter) + 1))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

void	handle_heredoc(t_cmd *cmd)
{
	int	fd;

	fd = open(".heredoc_tmp",
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	write_heredoc(fd, cmd->infile);
	close(fd);
	fd = open(".heredoc_tmp", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}
