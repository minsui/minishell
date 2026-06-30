/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan <chan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 19:24:21 by chan              #+#    #+#             */
/*   Updated: 2026/06/30 13:19:00 by chan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*new_token(char *value, t_token_type type, t_quote_type quote)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = value;
	new->type = type;
	new->quote = quote;
	new->next = NULL;
	return (new);
}

void	add_token_back(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!(*head))
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	print_tokens(t_token *head)
{
	while (head)
	{
		printf("TOKEN [%d] : %s\n",
			head->type,
			head->value);
		head = head->next;
	}
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->value);
		free(tmp);
	}
}
