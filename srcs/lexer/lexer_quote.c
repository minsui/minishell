/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan <chan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 19:24:08 by chan              #+#    #+#             */
/*   Updated: 2026/06/28 19:24:09 by chan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

void	handle_single_quote(char *line, int *i,
			char *word, int *j)
{
	(*i)++;
	while (line[*i] && line[*i] != '\'')
	{
		word[*j] = line[*i];
		(*j)++;
		(*i)++;
	}
	if (line[*i] == '\'')
		(*i)++;
}

void	handle_double_quote(char *line, int *i,
			char *word, int *j)
{
	(*i)++;
	while (line[*i] && line[*i] != '"')
	{
		word[*j] = line[*i];
		(*j)++;
		(*i)++;
	}
	if (line[*i] == '"')
		(*i)++;
}
