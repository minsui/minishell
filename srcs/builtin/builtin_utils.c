/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkim2 <mkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 21:51:59 by mkim2             #+#    #+#             */
/*   Updated: 2026/07/24 17:16:38 by mkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	is_valid_id(char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	if (s[0] >= '0' && s[0] <= '9')
		return (0);
	if (!ft_isalnum(s[0]) && s[0] != '_')
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	id_error(char *cmd, char *arg)
{
	ft_putstr("minishell: ", 2);
	ft_putstr(cmd, 2);
	ft_putstr(": `", 2);
	ft_putstr(arg, 2);
	ft_putstr("': not a valid identifier\n", 2);
}
