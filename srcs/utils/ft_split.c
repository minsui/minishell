/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chan <chan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 19:47:21 by chan              #+#    #+#             */
/*   Updated: 2026/06/29 19:47:22 by chan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static void	free_tab(char **tab, int size)
{
	while (size > 0)
		free(tab[--size]);
	free(tab);
}

static int	fill_tab(char **tab, char const *s, char c)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
		{
			tab[j] = ft_strndup((char *)s + start, i - start);
			if (!tab[j])
				return (free_tab(tab, j), 0);
			j++;
		}
	}
	tab[j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!tab)
		return (NULL);
	if (!fill_tab(tab, s, c))
		return (NULL);
	return (tab);
}
