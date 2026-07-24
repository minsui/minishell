/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkim2 <mkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 21:51:40 by mkim2             #+#    #+#             */
/*   Updated: 2026/07/23 22:01:23 by mkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_key_len(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

int	env_find(char **env, char *key)
{
	int	i;
	int	len;

	len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (env_key_len(env[i]) == len
			&& !ft_strncmp(env[i], key, len))
			return (i);
		i++;
	}
	return (-1);
}

static char	**env_grow(char **env, char *entry)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (env_size(env) + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = entry;
	new_env[i + 1] = NULL;
	free(env);
	return (new_env);
}

int	env_put(t_shell *shell, char *entry)
{
	char	*key;
	int		idx;

	if (!entry)
		return (1);
	key = ft_strndup(entry, env_key_len(entry));
	if (!key)
		return (1);
	idx = env_find(shell->env, key);
	free(key);
	if (idx >= 0)
	{
		free(shell->env[idx]);
		shell->env[idx] = entry;
		return (0);
	}
	shell->env = env_grow(shell->env, entry);
	if (!shell->env)
		return (1);
	return (0);
}

int	env_remove(t_shell *shell, char *key)
{
	int	idx;

	idx = env_find(shell->env, key);
	if (idx < 0)
		return (0);
	free(shell->env[idx]);
	while (shell->env[idx + 1])
	{
		shell->env[idx] = shell->env[idx + 1];
		idx++;
	}
	shell->env[idx] = NULL;
	return (0);
}
