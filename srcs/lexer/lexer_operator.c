/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan <chan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 19:24:05 by chan              #+#    #+#             */
/*   Updated: 2026/06/28 19:24:07 by chan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static t_token	*handle_pipe(int *i)
{
	(*i)++;
	return (new_token(ft_strdup("|"), PIPE, NO_QUOTE));
}

static t_token	*handle_input(char *line, int *i)
{
	if (line[*i + 1] == '<')
	{
		(*i) += 2;
		return (new_token(ft_strdup("<<"), HEREDOC, NO_QUOTE));
	}
	(*i)++;
	return (new_token(ft_strdup("<"), REDIR_IN, NO_QUOTE));
}

static t_token	*handle_output(char *line, int *i)
{
	if (line[*i + 1] == '>')
	{
		(*i) += 2;
		return (new_token(ft_strdup(">>"), APPEND, NO_QUOTE));
	}
	(*i)++;
	return (new_token(ft_strdup(">"), REDIR_OUT, NO_QUOTE));
}

t_token	*extract_operator(char *line, int *i)
{
	if (line[*i] == '|')
		return (handle_pipe(i));
	if (line[*i] == '<')
		return (handle_input(line, i));
	if (line[*i] == '>')
		return (handle_output(line, i));
	return (NULL);
}
