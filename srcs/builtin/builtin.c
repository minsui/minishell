/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkim2 <mkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 21:51:15 by mkim2             #+#    #+#             */
/*   Updated: 2026/07/23 22:00:27 by mkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "echo", 5) || !ft_strncmp(cmd, "cd", 3))
		return (1);
	if (!ft_strncmp(cmd, "pwd", 4) || !ft_strncmp(cmd, "env", 4))
		return (1);
	if (!ft_strncmp(cmd, "export", 7) || !ft_strncmp(cmd, "unset", 6))
		return (1);
	if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	char	*name;

	name = cmd->argv[0];
	if (!ft_strncmp(name, "echo", 5))
		return (builtin_echo(cmd->argv));
	if (!ft_strncmp(name, "pwd", 4))
		return (builtin_pwd());
	if (!ft_strncmp(name, "env", 4))
		return (builtin_env(shell));
	if (!ft_strncmp(name, "cd", 3))
		return (builtin_cd(cmd->argv, shell));
	if (!ft_strncmp(name, "export", 7))
		return (builtin_export(cmd->argv, shell));
	if (!ft_strncmp(name, "unset", 6))
		return (builtin_unset(cmd->argv, shell));
	if (!ft_strncmp(name, "exit", 5))
		return (builtin_exit(cmd->argv, shell));
	return (0);
}
