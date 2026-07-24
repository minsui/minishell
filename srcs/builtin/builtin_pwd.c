/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkim2 <mkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 20:43:19 by mkim2             #+#    #+#             */
/*   Updated: 2026/07/24 17:16:24 by mkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_pwd(void)
{
	char	buf[4096];

	if (!getcwd(buf, sizeof(buf)))
	{
		perror("minishell: pwd");
		return (1);
	}
	ft_putstr(buf, 1);
	ft_putstr("\n", 1);
	return (0);
}
