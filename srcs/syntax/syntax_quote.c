/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan <chan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 19:24:34 by chan              #+#    #+#             */
/*   Updated: 2026/06/28 19:24:35 by chan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	skip_quote(char *line, int *i)
{
	char	quote;

	quote = line[*i];
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (!line[*i])
		return (1);
	(*i)++;
	return (0);
}

int	check_quote_syntax(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (skip_quote(line, &i))
				return (1);
		}
		else
			i++;
	}
	return (0);
}
