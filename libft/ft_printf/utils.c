/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:29 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 13:02:32 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Fills string s with width characters c.
*/

int			fillwc(char *s, int width, char c)
{
	int		count;

	count = 0;
	while (width-- > 0)
		s[count++] = c;
	return (count);
}

/*
** Returns the string with all lower case letters converted to upper case.
*/

char		*ft_toupper(char *s)
{
	int		i;

	if (!s)
		return (0);
	i = -1;
	while (s[++i])
		s[i] -= s[i] >= 'a' && s[i] <= 'z' ? 'a' - 'A' : 0;
	return (s);
}

void		skip_digits(char **s)
{
	while (**s >= '0' && **s <= '9')
		++*s;
}
