#include "../../includes/minishell.h"
#include <sys/wait.h>

static void	wait_children(int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		wait(NULL);
		i++;
	}
}

void	execute_pipeline(t_cmd *cmds, char **envp)
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid;
	int		count;

	prev_fd = -1;
	count = 0;
	while (cmds)
	{
		if (cmds->next)
			pipe(fd);
		pid = fork();
		if (pid == 0)
			exec_child(cmds, prev_fd, fd, envp);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmds->next)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		cmds = cmds->next;
		count++;
	}
	wait_children(count);
}
