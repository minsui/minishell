#include "../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	if (!ft_strncmp(cmd, "env", 4))
		return (1);
	if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	if (!ft_strncmp(cmd, "export", 7))
		return (1);
	if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	return (0);
}

int	execute_builtin(t_cmd *cmd, char ***envp)
{
	if (!ft_strncmp(cmd->argv[0], "echo", 5))
		return (builtin_echo(cmd->argv));
	if (!ft_strncmp(cmd->argv[0], "pwd", 4))
		return (builtin_pwd());
	if (!ft_strncmp(cmd->argv[0], "env", 4))
		return (builtin_env(*envp));
	if (!ft_strncmp(cmd->argv[0], "cd", 3))
		return (builtin_cd(cmd->argv));
	if (!ft_strncmp(cmd->argv[0], "exit", 5))
		return (builtin_exit(cmd->argv));
	if (!ft_strncmp(cmd->argv[0], "export", 7))
		return (builtin_export(cmd->argv, envp));
	if (!ft_strncmp(cmd->argv[0], "unset", 6))
		return (builtin_unset(cmd->argv, envp));
	return (1);
}
