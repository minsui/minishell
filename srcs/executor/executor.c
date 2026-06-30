#include "../../includes/minishell.h"
#include <sys/wait.h>

static void	child_process(t_cmd *cmd, char **envp)
{
	char	*path;

	setup_child_signals();
	handle_redirection(cmd);
	path = get_path(cmd->argv[0], envp);
	if (!path)
	{
		printf("%s: command not found\n", cmd->argv[0]);
		exit(127);
	}
	execve(path, cmd->argv, envp);
	perror(cmd->argv[0]);
	free(path);
	exit(1);
}

void	execute_command(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		child_process(cmd, shell->env);
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		shell->exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit (core dumped)\n", 20);
	}
}

void	execute(t_cmd *cmds, t_shell *shell)
{
	if (!cmds)
		return ;
	if (cmds->next)
		execute_pipeline(cmds, shell->env);
	else
		execute_command(cmds, shell);
}
