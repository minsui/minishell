/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan <chan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 19:23:50 by chan              #+#    #+#             */
/*   Updated: 2026/06/29 18:30:52 by chan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_exit_status(t_shell *shell)
{
	return (ft_itoa(shell->exit_status));
}

char	*get_env_value(char *name, t_shell *shell)
{
	int		i;
	size_t	len;

	if (!ft_strncmp(name, "?", 2))
		return (get_exit_status(shell));
	i = 0;
	len = ft_strlen(name);
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], name, len)
			&& shell->env[i][len] == '=')
			return (ft_strdup(shell->env[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}
