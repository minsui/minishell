/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkim2 <mkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 19:25:01 by chan              #+#    #+#             */
/*   Updated: 2026/07/24 17:09:25 by mkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_signal = 0;

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
	shell->tokens = lexer(line);
	if (check_syntax(line, shell->tokens))
	{
		free_tokens(shell->tokens);
		shell->tokens = NULL;
		return ;
	}
	expand_tokens(shell->tokens, shell);
	shell->cmds = parse_tokens(shell->tokens);
	execute(shell->cmds, shell);
	free_tokens(shell->tokens);
	free_cmds(shell->cmds);
	shell->tokens = NULL;
	shell->cmds = NULL;
}

void	shell_loop(t_shell *shell)
{
	char	*line;

	setup_signals();
	while (1)
	{
		line = readline("minishell$ ");
		if (g_signal == SIGINT) 
		{
			shell->exit_status = 130;
			g_signal = 0;
		}
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
