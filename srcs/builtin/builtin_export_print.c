/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkim2 <mkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 21:52:22 by mkim2             #+#    #+#             */
/*   Updated: 2026/07/24 17:17:12 by mkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**sorted_copy(char **env)
{
	char	**arr;
	int		i;

	arr = malloc(sizeof(char *) * (env_size(env) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env[i])
	{
		arr[i] = env[i];
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

static void	sort_arr(char **arr)
{
	char	*tmp;
	int		i;

	i = 0;
	while (arr[i] && arr[i + 1])
	{
		if (ft_strcmp(arr[i], arr[i + 1]) > 0)
		{
			tmp = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

static void	print_one(char *entry)
{
	int	len;

	len = env_key_len(entry);
	ft_putstr("declare -x ", 1);
	write(1, entry, len);
	if (entry[len] == '=')
	{
		ft_putstr("=\"", 1);
		ft_putstr(entry + len + 1, 1);
		ft_putstr("\"", 1);
	}
	ft_putstr("\n", 1);
}

int	print_export(t_shell *shell)
{
	char	**arr;
	int		i;

	arr = sorted_copy(shell->env);
	if (!arr)
		return (1);
	sort_arr(arr);
	i = 0;
	while (arr[i])
	{
		print_one(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}
