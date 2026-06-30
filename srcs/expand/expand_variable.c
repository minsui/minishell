/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan <chan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 19:46:51 by chan              #+#    #+#             */
/*   Updated: 2026/06/29 19:46:54 by chan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*append_char(char *result, char c)
{
	char	str[2];
	char	*tmp;

	str[0] = c;
	str[1] = '\0';
	tmp = ft_strjoin(result, str);
	free(result);
	return (tmp);
}

static char	*append_env(char *result,
				char *name, t_shell *shell)
{
	char	*value;
	char	*tmp;

	value = get_env_value(name, shell);
	tmp = ft_strjoin(result, value);
	free(result);
	free(value);
	return (tmp);
}

static char	*get_var_name(char *str, int *i)
{
	int		start;

	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	start = *i;
	while (str[*i]
		&& (ft_isalnum(str[*i])
			|| str[*i] == '_'))
		(*i)++;
	return (ft_strndup(str + start, *i - start));
}

char	*expand_variable(char *str, t_shell *shell)
{
	char	*result;
	char	*name;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			name = get_var_name(str, &i);
			result = append_env(result, name, shell);
			free(name);
		}
		else
			result = append_char(result, str[i++]);
	}
	return (result);
}
