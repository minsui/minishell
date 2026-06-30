/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan <chan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 19:25:01 by chan              #+#    #+#             */
/*   Updated: 2026/06/29 20:08:56 by chan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_syntax(char *line, t_token *tokens)
{
	if (check_quote_syntax(line))
	{
		printf("syntax error: unclosed quote\n");
		return (1);
	}
	if (check_pipe_syntax(tokens))
	{
		printf("syntax error near unexpected token `|'\n");
		return (1);
	}
	if (check_redir_syntax(tokens))
	{
		printf("syntax error near redirection\n");
		return (1);
	}
	return (0);
}

static void	process_line(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmd;

	tokens = lexer(line);
	if (check_syntax(line, tokens))
	{
		free_tokens(tokens);
		return ;
	}
	expand_tokens(tokens, shell);
	print_tokens(tokens);
	cmd = parse_tokens(tokens);
	execute(cmd, shell);
	free_tokens(tokens);
	free_cmds(cmd);
}

void	shell_loop(t_shell *shell)
{
	char	*line;

	setup_signals();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		process_line(line, shell);
		free(line);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	shell.env = copy_env(envp);
	shell.exit_status = 0;
	shell_loop(&shell);
	free_split(shell.env);
	return (0);
}
