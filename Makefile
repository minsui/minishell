NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror

SRC         =   srcs/main.c \
                srcs/lexer/lexer.c \
                srcs/lexer/lexer_word.c \
                srcs/lexer/lexer_operator.c \
                srcs/lexer/lexer_utils.c \
                srcs/lexer/lexer_word_utils.c \
                srcs/lexer/lexer_quote.c \
                srcs/lexer/token.c \
                srcs/parser/parser.c \
                srcs/parser/parser_command.c \
                srcs/parser/parser_utils.c \
                srcs/syntax/syntax_pipe.c \
                srcs/syntax/syntax_redir.c \
				srcs/syntax/syntax_quote.c \
                srcs/executor/executor.c \
				srcs/executor/executor_utils.c \
                srcs/executor/path_utils.c \
                srcs/executor/path.c \
                srcs/executor/pipe.c \
                srcs/executor/pipe_child.c \
                srcs/executor/redirection.c \
                srcs/executor/heredoc.c \
				srcs/executor/heredoc_utils.c \
                srcs/expand/expand.c \
                srcs/expand/expand_utils.c \
				srcs/expand/expand_variable.c \
                srcs/signals/signals.c \
                srcs/utils/env_utils.c \
				srcs/utils/ft_isalnum.c \
                srcs/utils/ft_strndup.c \
                srcs/utils/ft_strdup.c \
                srcs/utils/ft_strlen.c \
				srcs/utils/ft_strjoin.c \
                srcs/utils/ft_strjoin3.c \
                srcs/utils/ft_split.c \
				srcs/utils/ft_strncmp.c \
                srcs/utils/ft_itoa.c \
				srcs/utils/ft_putstr.c\
				srcs/utils/cleanup.c\
				srcs/builtin/builtin_cd.c\
				srcs/builtin/builtin_echo.c\
				srcs/builtin/builtin_env.c\
				srcs/builtin/builtin_exit.c\
				srcs/builtin/builtin_export_print.c\
				srcs/builtin/builtin_export.c\
				srcs/builtin/builtin_pwd.c\
				srcs/builtin/builtin_unset.c\
				srcs/builtin/builtin_utils.c\
				srcs/builtin/builtin.c\
				srcs/builtin/env_tools.c

OBJ_DIR     = obj
OBJ         = $(patsubst srcs/%, $(OBJ_DIR)/%, $(SRC:.c=.o))

INCLUDES    = -Iincludes

READLINE    = -lreadline

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(READLINE) -o $(NAME)

$(OBJ_DIR)/%.o: srcs/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re