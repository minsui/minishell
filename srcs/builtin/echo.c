#include "../../includes/minishell.h"

int	builtin_echo(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
	return (0);
}
