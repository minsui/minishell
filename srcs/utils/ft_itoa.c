/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkim2 <mkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 19:47:15 by chan              #+#    #+#             */
/*   Updated: 2026/07/24 16:43:55 by mkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_itoa(int n)
{
	char	buffer[12];
	int		i;
	int		neg;

	i = 11;
	neg = (n < 0);
	buffer[i--] = '\0';
	if (n == 0)
		buffer[i--] = '0';
	while (n != 0)
	{
		if (neg)
			buffer[i--] = -(n % 10) + '0';
		else
			buffer[i--] = (n % 10) + '0';
		n /= 10;
	}
	if (neg)
		buffer[i--] = '-';
	return (ft_strdup(&buffer[i + 1]));
}
