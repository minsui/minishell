/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan <chan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 19:47:25 by chan              #+#    #+#             */
/*   Updated: 2026/06/29 19:47:26 by chan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*str;
	int		i;
	int		k;

	str = malloc(ft_strlen(s1)
			+ ft_strlen(s2)
			+ ft_strlen(s3) + 1);
	if (!str)
		return (NULL);
	i = 0;
	k = 0;
	while (s1[i])
		str[k++] = s1[i++];
	i = 0;
	while (s2[i])
		str[k++] = s2[i++];
	i = 0;
	while (s3[i])
		str[k++] = s3[i++];
	str[k] = '\0';
	return (str);
}
