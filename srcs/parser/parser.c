/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan <chan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 19:24:29 by chan              #+#    #+#             */
/*   Updated: 2026/06/29 19:55:52 by chan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*new;

	head = NULL;
	while (tokens)
	{
		new = create_cmd(tokens);
		add_cmd_back(&head, new);
		while (tokens && tokens->type != PIPE)
			tokens = tokens->next;
		if (tokens)
			tokens = tokens->next;
	}
	return (head);
}
