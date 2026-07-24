/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkim2 <mkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 19:25:10 by chan              #+#    #+#             */
/*   Updated: 2026/07/24 17:13:45 by mkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
}	t_token_type;

typedef enum e_quote_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_quote_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_quote_type	quote;
	struct s_token	*next;
}	t_token;

typedef struct s_lexer
{
	char			*line;
	int				i;
	t_quote_type	quote;
}	t_lexer;

typedef struct s_cmd
{
	char			**argv;
	char			*infile;
	char			*outfile;
	int				append;
	int				heredoc;
	int				heredoc_fd;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	char	**env;
	int		exit_status;
	t_token	*tokens;
	t_cmd	*cmds;
}	t_shell;

void	shell_cleanup(t_shell *shell);

extern int g_signal;

/* builtin */
int		is_builtin(char *cmd);
int		execute_builtin(t_cmd *cmd, t_shell *shell);
int		builtin_echo(char **argv);
int		builtin_pwd(void);
int		builtin_env(t_shell *shell);
int		builtin_cd(char **argv, t_shell *shell);
int		builtin_exit(char **argv, t_shell *shell);
int		builtin_export(char **argv, t_shell *shell);
int		builtin_unset(char **argv, t_shell *shell);
int		print_export(t_shell *shell);
int		is_valid_id(char *s);
void	id_error(char *cmd, char *arg);
int		ft_strcmp(char *s1, char *s2);

/* env */
int		env_key_len(char *s);
int		env_find(char **env, char *key);
int		env_put(t_shell *shell, char *entry);
int		env_remove(t_shell *shell, char *key);

/* executor */
char	*get_path(char *cmd, char **envp);
char	*find_env(char *name, char **envp);
void	free_split(char **arr);
void	execute(t_cmd *cmds, t_shell *shell);
void	execute_pipeline(t_cmd *cmds, t_shell *shell);
void	execute_command(t_cmd *cmd, t_shell *shell);
int		handle_redirection(t_cmd *cmd);
void	exec_child(t_cmd *cmd, int prev_fd, int *fd, t_shell *shell);
void	run_builtin_in_parent(t_cmd *cmd, t_shell *shell);
void	child_process(t_cmd *cmd, t_shell *shell);
void	store_status(int status, t_shell *shell);
int		fill_heredoc_pipe(char *delimiter);
int		prepare_heredocs(t_cmd *cmds, t_shell *shell);
void	close_heredocs(t_cmd *cmds);

/* expand */
void	expand_tokens(t_token *tokens, t_shell *shell);
char	*expand_variable(char *str, t_shell *shell);
char	*get_env_value(char *name, t_shell *shell);

/* lexer */
t_token	*lexer(char *line);
t_token	*extract_operator(char *line, int *i);
char	*extract_word(t_lexer *lx);
int		is_quote(char c);
void	handle_single_quote(char *line, int *i, char *word, int *j);
void	handle_double_quote(char *line, int *i, char *word, int *j);
int		is_operator(char c);
int		word_len(char *line, int i);
void	skip_spaces(char *line, int *i);

/* token */
t_token	*new_token(char *value, t_token_type type, t_quote_type quote);
void	add_token_back(t_token **head, t_token *new);
void	free_tokens(t_token *head);

/* parser */
t_cmd	*parse_tokens(t_token *tokens);
void	free_cmds(t_cmd *cmds);
void	add_cmd_back(t_cmd **head, t_cmd *new);
char	**fill_argv(t_token *tokens);
void	parse_redirection(t_cmd *cmd, t_token *tokens);
t_cmd	*create_cmd(t_token *tokens);
int		count_args(t_token *tokens);
int		is_redirection(t_token_type type);

/* signals */
void	setup_signals(void);
void	setup_child_signals(void);

/* syntax */
int		check_quote_syntax(char *line);
int		check_pipe_syntax(t_token *tokens);
int		check_redir_syntax(t_token *tokens);

/* utils */
char	**copy_env(char **envp);
int		env_size(char **envp);
char	*ft_strndup(char *src, int len);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isalnum(int c);
char	*ft_itoa(int n);
void	ft_putstr(char *s, int fd);

/* main */
void	shell_loop(t_shell *shell);

#endif