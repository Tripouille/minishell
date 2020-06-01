/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_basics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:29 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 13:02:32 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** If there is no conversion, collects characters in buffer
** until next conversion or end of format is reached.
** Sets options[MW] (*len) to the number of collected chars.
*/

char		*collectchars(char **s, int *len)
{
	char	*res;
	long	i;

	i = 0;
	while ((*s)[i] && (*s)[i] != '%')
		i++;
	if (!(res = malloc(sizeof(*res) * (i + 1))))
		return (0);
	i = 0;
	while (**s && **s != '%')
	{
		res[i++] = **s;
		++*s;
	}
	*len = i;
	return (res);
}

/*
** Conversion for %c.
*/

char		*getcharac(va_list va, int *options)
{
	char		*s;
	char		c;

	if (options[LM] == L)
		return (getwcharac(va, options));
	c = (unsigned char)(va_arg(va, int));
	options[MW] = max(options[MW], 1);
	if (!(s = malloc(sizeof(*s) * ((long)options[MW] + 1))))
		return (0);
	s[options[LEFT] ? 0 : options[MW] - 1] = c;
	fillwc(options[LEFT] ? s + 1 : s, options[MW] - 1, ' ');
	return (s);
}

/*
** Conversion for %s.
*/

char		*getstr(va_list va, int *options)
{
	char	*arg;
	char	*s;
	int		argsize;
	int		i;

	if (options[LM] == L)
		return (getwstr(va, options));
	arg = va_arg(va, char*);
	arg = !arg ? "(null)" : arg;
	argsize = 0;
	if (options[ACC])
		argsize = ft_strlen(arg);
	if (options[ACC] >= 0)
		argsize = min(argsize, options[ACC]);
	options[MW] = max(options[MW], argsize);
	if (!(s = malloc(sizeof(*s) * ((long)options[MW] + 1))))
		return (0);
	fillwc(s, options[MW], options[ZERO] ? '0' : ' ');
	i = options[LEFT] ? 0 : options[MW] - argsize;
	ft_strncpy(s + i, arg, argsize);
	return (s);
}

/*
** Conversion for %%.
*/

char		*getpercent(va_list va, int *options)
{
	char	*s;
	char	c;

	(void)va;
	if (!options[MW])
		options[MW] = 1;
	if (!(s = malloc(sizeof(*s) * ((long)options[MW] + 1))))
		return (0);
	s[options[LEFT] ? 0 : options[MW] - 1] = '%';
	c = options[ZERO] ? '0' : ' ';
	fillwc(options[LEFT] ? s + 1 : s, options[MW] - 1, c);
	return (s);
}
