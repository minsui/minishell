#include "../../includes/minishell.h"

int	builtin_exit(char **argv)
{
	(void)argv;
	printf("exit\n");
	exit(0);
}
