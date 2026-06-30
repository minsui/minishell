#include "../../includes/minishell.h"

void	exec_child(t_cmd *cmd,
		int prev_fd, int *fd,
		char **envp)
{
	char	*path;

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
	handle_redirection(cmd);
	path = get_path(cmd->argv[0], envp);
	if (!path)
	{
		printf("%s: command not found\n",
			cmd->argv[0]);
		exit(EXIT_FAILURE);
	}
	execve(path, cmd->argv, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}
