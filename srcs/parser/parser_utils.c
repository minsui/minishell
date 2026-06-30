/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan <chan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 19:24:27 by chan              #+#    #+#             */
/*   Updated: 2026/06/29 20:08:33 by chan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirection(t_token_type type)
{
	return (type == REDIR_IN
		|| type == REDIR_OUT
		|| type == APPEND
		|| type == HEREDOC);
}

int	count_args(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == WORD)
			count++;
		else if (is_redirection(tokens->type))
			tokens = tokens->next;
		tokens = tokens->next;
	}
	return (count);
}

void	add_cmd_back(t_cmd **head, t_cmd *new)
{
	t_cmd	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

// void	print_commands(t_cmd *cmds)
// {
// 	int	i;

// 	while (cmds)
// 	{
// 		i = 0;
// 		printf("COMMAND\n");
// 		while (cmds->argv[i])
// 		{
// 			printf("argv[%d] = %s\n",
// 				i, cmds->argv[i]);
// 			i++;
// 		}
// 		if (cmds->infile)
// 			printf("infile : %s\n",
// 				cmds->infile);
// 		if (cmds->outfile)
// 			printf("outfile : %s\n",
// 				cmds->outfile);
// 		if (cmds->append)
// 			printf("append mode\n");
// 		if (cmds->heredoc)
// 			printf("heredoc mode\n");
// 		cmds = cmds->next;
// 	}
// }

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	int		i;

	while (cmds)
	{
		i = 0;
		while (cmds->argv && cmds->argv[i])
		{
			free(cmds->argv[i]);
			i++;
		}
		free(cmds->argv);
		free(cmds->infile);
		free(cmds->outfile);
		tmp = cmds;
		cmds = cmds->next;
		free(tmp);
	}
}
