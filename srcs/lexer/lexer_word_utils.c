/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan <chan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 19:24:13 by chan              #+#    #+#             */
/*   Updated: 2026/06/28 19:24:14 by chan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	skip_quote(char *line, int *i, int *len)
{
	char	quote;

	quote = line[*i];
	(*i)++;
	while (line[*i] && line[*i] != quote)
	{
		(*len)++;
		(*i)++;
	}
	if (line[*i] == quote)
		(*i)++;
}

int	word_len(char *line, int i)
{
	int	len;

	len = 0;
	while (line[i]
		&& line[i] != ' '
		&& line[i] != '\t'
		&& !is_operator(line[i]))
	{
		if (is_quote(line[i]))
			skip_quote(line, &i, &len);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}
