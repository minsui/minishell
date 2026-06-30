/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan <chan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 19:24:17 by chan              #+#    #+#             */
/*   Updated: 2026/06/30 13:26:52 by chan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*lexer(char *line)
{
	t_lexer	lx;
	t_token	*head;
	t_token	*token;
	char	*word;

	lx.line = line;
	lx.i = 0;
	lx.quote = NO_QUOTE;
	head = NULL;
	while (lx.line[lx.i])
	{
		skip_spaces(lx.line, &lx.i);
		if (!lx.line[lx.i])
			break ;
		if (is_operator(lx.line[lx.i]))
			token = extract_operator(lx.line, &lx.i);
		else
		{
			word = extract_word(&lx);
			token = new_token(word, WORD, lx.quote);
		}
		add_token_back(&head, token);
	}
	return (head);
}
