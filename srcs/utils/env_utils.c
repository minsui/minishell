/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan <chan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 19:47:11 by chan              #+#    #+#             */
/*   Updated: 2026/06/29 19:47:13 by chan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	**copy_env(char **envp)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *)
			* (env_size(envp) + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}
