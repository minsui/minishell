#include "../../includes/minishell.h"

static int	match_key(char *env, char *key)
{
	int	len;

	len = ft_strlen(key);
	return (!ft_strncmp(env, key, len)
		&& env[len] == '=');
}

int	builtin_unset(char **argv, char ***envp)
{
	int	i;
	int	j;

	if (!argv[1])
		return (0);
	i = 0;
	while ((*envp)[i])
	{
		if (match_key((*envp)[i], argv[1]))
		{
			free((*envp)[i]);
			j = i;
			while ((*envp)[j])
			{
				(*envp)[j] = (*envp)[j + 1];
				j++;
			}
			break ;
		}
		i++;
	}
	return (0);
}
