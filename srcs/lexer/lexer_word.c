/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan <chan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 19:24:15 by chan              #+#    #+#             */
/*   Updated: 2026/06/30 13:23:06 by chan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	copy_char(t_lexer *lx, char *word, int *j)
{
	word[*j] = lx->line[lx->i];
	(*j)++;
	lx->i++;
}

static void	handle_quote(t_lexer *lx, char *word, int *j)
{
	if (lx->line[lx->i] == '\'')
	{
		lx->quote = SINGLE_QUOTE;
		handle_single_quote(lx->line, &lx->i, word, j);
	}
	else if (lx->line[lx->i] == '"')
	{
		lx->quote = DOUBLE_QUOTE;
		handle_double_quote(lx->line, &lx->i, word, j);
	}
	else
		copy_char(lx, word, j);
}

char	*extract_word(t_lexer *lx)
{
	char	*word;
	int		j;

	lx->quote = NO_QUOTE;
	word = malloc(word_len(lx->line, lx->i) + 1);
	if (!word)
		return (NULL);
	j = 0;
	while (lx->line[lx->i]
		&& lx->line[lx->i] != ' '
		&& lx->line[lx->i] != '\t'
		&& !is_operator(lx->line[lx->i]))
	{
		handle_quote(lx, word, &j);
	}
	word[j] = '\0';
	return (word);
}
