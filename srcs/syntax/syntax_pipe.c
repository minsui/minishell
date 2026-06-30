/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan <chan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 19:24:32 by chan              #+#    #+#             */
/*   Updated: 2026/06/29 19:48:24 by chan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_invalid_pipe(t_token *prev, t_token *curr)
{
	if (!prev)
		return (1);
	if (!curr->next)
		return (1);
	if (prev->type == PIPE)
		return (1);
	if (curr->next->type == PIPE)
		return (1);
	return (0);
}

int	check_pipe_syntax(t_token *tokens)
{
	t_token	*prev;

	prev = NULL;
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			if (is_invalid_pipe(prev, tokens))
				return (1);
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (0);
}
