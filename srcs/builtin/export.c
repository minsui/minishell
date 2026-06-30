#include "../../includes/minishell.h"

static void	add_env(char *str, char ***envp)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *)
			* (env_size(*envp) + 2));
	if (!new_env)
		return ;
	i = 0;
	while ((*envp)[i])
	{
		new_env[i] = ft_strdup((*envp)[i]);
		i++;
	}
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = NULL;
	free_split(*envp);
	*envp = new_env;
}

int	builtin_export(char **argv, char ***envp)
{
	if (!argv[1])
		return (0);
	add_env(argv[1], envp);
	return (0);
}
