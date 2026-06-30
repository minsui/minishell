/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan <chan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 19:56:13 by chan              #+#    #+#             */
/*   Updated: 2026/06/29 20:02:21 by chan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**fill_argv(t_token *tokens)
{
	char	**argv;
	int		i;

	argv = malloc(sizeof(char *) * (count_args(tokens) + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == WORD)
			argv[i++] = ft_strdup(tokens->value);
		else if (is_redirection(tokens->type))
			tokens = tokens->next;
		tokens = tokens->next;
	}
	argv[i] = NULL;
	return (argv);
}

void	parse_redirection(t_cmd *cmd, t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == REDIR_IN)
			cmd->infile = ft_strdup(tokens->next->value);
		else if (tokens->type == REDIR_OUT)
			cmd->outfile = ft_strdup(tokens->next->value);
		else if (tokens->type == APPEND)
		{
			cmd->outfile = ft_strdup(tokens->next->value);
			cmd->append = 1;
		}
		else if (tokens->type == HEREDOC)
		{
			cmd->infile = ft_strdup(tokens->next->value);
			cmd->heredoc = 1;
		}
		tokens = tokens->next;
	}
}

t_cmd	*create_cmd(t_token *tokens)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = fill_argv(tokens);
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->heredoc = 0;
	cmd->next = NULL;
	parse_redirection(cmd, tokens);
	return (cmd);
}
