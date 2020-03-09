/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 04:32:51 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/09 06:49:42 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		copy_strings(char *join, char **strings, int nb)
{
	int		i;
	int		c;

	i = -1;
	c = 0;
	while (++i < nb)
		while (*strings[i])
			join[c++] = *strings[i]++;
}

char			*ft_strjoin(int nb, ...)
{
	va_list		va;
	char		*join;
	char		*strings[nb];
	int			size;
	int			i;

	va_start(va, nb);
	size = 1;
	i = -1;
	while (++i < nb)
	{
		strings[i] = va_arg(va, char *);
		size += slen(strings[i]);
	}
	va_end(va);
	if (!(join = ft_calloc(sizeof(char), size)))
		return (0);
	copy_strings(join, strings, nb);
	return (join);
}
