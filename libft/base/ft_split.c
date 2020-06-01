/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 06:51:15 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/23 18:35:46 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"

static int		ft_wordcount(char const *str, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		count += str[i] ? 1 : 0;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static int		ft_wsize(char const *str, char c)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char		**ft_free_all(char **split, int i)
{
	while (--i >= 0)
		free(split[i]);
	free(split);
	return (0);
}

static char		**ft_fillsplit(char **split, char const *str, char c,
								int word_nb)
{
	int		wsize;
	int		istr;
	int		i;
	int		j;

	istr = 0;
	i = -1;
	while (++i < word_nb)
	{
		while (str[istr] && str[istr] == c)
			istr++;
		wsize = ft_wsize(str + istr, c);
		if (!(split[i] = malloc(sizeof(**split) * (1 + wsize))))
			return (ft_free_all(split, i));
		split[i][wsize] = 0;
		j = 0;
		while (str[istr] && str[istr] != c)
			split[i][j++] = str[istr++];
	}
	return (split);
}

char			**ft_split(char const *s, char c)
{
	char	**split;
	int		word_nb;

	if (!s)
		return (0);
	word_nb = ft_wordcount(s, c);
	if (!(split = malloc(sizeof(*split) * (word_nb + 1))))
		return (0);
	split[word_nb] = 0;
	return (ft_fillsplit(split, s, c, word_nb));
}
