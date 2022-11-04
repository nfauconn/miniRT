/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:12:01 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/04 16:24:32 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	line_nb(char const *s)
{
	int		i;
	int		line_nb;

	i = 0;
	while (s[i] && (ft_iswhitespace(s[i])))
		i++;
	line_nb = 0;
	while (s[i])
	{
		while (s[i] && !ft_iswhitespace(s[i]))
			i++;
		line_nb++;
		while (s[i] && ft_iswhitespace(s[i]))
			i++;
	}
	return (line_nb);
}

static int	len_until_whitespace(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && !ft_iswhitespace(s[i]))
		i++;
	return (i);
}

static void	clear_tab(char **tab, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	*fill_tab(const char *s, int *i)
{
	char	*tab_line;
	int		j;

	tab_line = malloc(sizeof(char) * (len_until_whitespace(s + *i) + 1));
	if (!s)
		return (NULL);
	j = 0;
	while (s[*i] && !ft_iswhitespace(s[*i]))
		tab_line[j++] = s[(*i)++];
	tab_line[j] = '\0';
	return (tab_line);
}

char	**ft_split_whitespace(char const *s)
{
	char	**tab;
	int		index;
	int		i;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (line_nb(s) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	index = 0;
	while (s[i] && (index < line_nb(s)))
	{
		while (s[i] && ft_iswhitespace(s[i]))
			i++;
		tab[index] = fill_tab(s, &i);
		if (!tab[index])
		{	
			clear_tab(tab, index);
			return (NULL);
		}
		index++;
	}
	tab[index] = NULL;
	return (tab);
}
