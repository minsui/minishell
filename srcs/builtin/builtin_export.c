/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkim2 <mkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 21:25:51 by mkim2             #+#    #+#             */
/*   Updated: 2026/07/23 22:01:10 by mkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	export_one(char *arg, t_shell *shell)
{
	int	len;

	if (!is_valid_id(arg))
	{
		id_error("export", arg);
		return (1);
	}
	len = env_key_len(arg);
	if (arg[len] != '=' && env_find(shell->env, arg) >= 0)
		return (0);
	return (env_put(shell, ft_strdup(arg)));
}

int	builtin_export(char **argv, t_shell *shell)
{
	int	i;
	int	ret;

	if (!argv[1])
		return (print_export(shell));
	ret = 0;
	i = 1;
	while (argv[i])
	{
		if (export_one(argv[i], shell))
			ret = 1;
		i++;
	}
	return (ret);
}
