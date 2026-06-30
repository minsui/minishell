/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan <chan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 19:24:01 by chan              #+#    #+#             */
/*   Updated: 2026/06/29 18:30:22 by chan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_tokens(t_token *tokens, t_shell *shell)
{
	char	*new_value;

	while (tokens)
	{
		if (tokens->type == WORD
			&& tokens->quote != SINGLE_QUOTE)
		{
			new_value = expand_variable(tokens->value, shell);
			free(tokens->value);
			tokens->value = new_value;
		}
		tokens = tokens->next;
	}
}
