/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkim2 <mkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 21:26:07 by mkim2             #+#    #+#             */
/*   Updated: 2026/07/24 17:15:10 by mkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*cd_target(char **argv, t_shell *shell)
{
	char	*home;

	if (argv[1])
		return (argv[1]);
	home = find_env("HOME", shell->env);
	if (!home)
		ft_putstr("minishell: cd: HOME not set\n", 2);
	return (home);
}

static void	update_pwd(t_shell *shell, char *oldpwd)
{
	char	buf[4096];

	env_put(shell, ft_strjoin("OLDPWD=", oldpwd));
	if (getcwd(buf, sizeof(buf)))
		env_put(shell, ft_strjoin("PWD=", buf));
}

int	builtin_cd(char **argv, t_shell *shell)
{
	char	oldpwd[4096];
	char	*target;

	if (!getcwd(oldpwd, sizeof(oldpwd)))
		oldpwd[0] = '\0';
	target = cd_target(argv, shell);
	if (!target)
		return (1);
	if (chdir(target) != 0)
	{
		ft_putstr("minishell: cd: ", 2);
		perror(target);
		return (1);
	}
	update_pwd(shell, oldpwd);
	return (0);
}
