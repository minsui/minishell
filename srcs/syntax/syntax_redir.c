/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan <chan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 19:24:36 by chan              #+#    #+#             */
/*   Updated: 2026/06/29 20:05:46 by chan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	invalid_redir(t_token *token)
{
	if (!token->next)
		return (1);
	if (token->next->type != WORD)
		return (1);
	return (0);
}

int	check_redir_syntax(t_token *tokens)
{
	while (tokens)
	{
		if (is_redirection(tokens->type))
		{
			if (invalid_redir(tokens))
				return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}
