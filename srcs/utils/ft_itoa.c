/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan <chan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 19:47:15 by chan              #+#    #+#             */
/*   Updated: 2026/06/29 19:47:19 by chan             ###   ########.fr       */
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
	if (neg)
		n = -n;
	while (n > 0)
	{
		buffer[i--] = (n % 10) + '0';
		n /= 10;
	}
	if (neg)
		buffer[i--] = '-';
	return (ft_strdup(&buffer[i + 1]));
}
