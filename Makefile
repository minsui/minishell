NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror

SRC         =   srcs/main.c \
                srcs/main_global.c \
                srcs/builtin/builtin.c \
                srcs/builtin/echo.c \
                srcs/builtin/pwd.c \
                srcs/builtin/env.c \
                srcs/builtin/cd.c \
                srcs/builtin/exit.c \
                srcs/builtin/export.c \
                srcs/builtin/unset.c \
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
                srcs/executor/path_utils.c \
                srcs/executor/path.c \
                srcs/executor/pipe.c \
                srcs/executor/pipe_child.c \
                srcs/executor/redirection.c \
                srcs/executor/heredoc.c \
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
                srcs/utils/ft_itoa.c

OBJ_DIR     = obj
OBJ         = $(patsubst srcs/%, $(OBJ_DIR)/%, $(SRC:.c=.o))

INCLUDES    = -Iinclude

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