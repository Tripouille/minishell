/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:29 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 13:02:32 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Calculates the correct mask in function of number of bytes,
** then adds the number in the mask.
*/

wchar_t		unicode(wchar_t n, int bytes)
{
	unsigned int	result;
	int				pm;
	int				pd;
	int				i;

	result = 0;
	pm = 15;
	i = -1;
	while (++i < bytes - 1)
	{
		result += ft_pow(2, pm);
		pm += 8;
	}
	pm = 7;
	while (i-- >= 0)
		result += ft_pow(2, pm--);
	pm = (8 * (bytes - 1));
	pd = 0;
	while (bytes--)
	{
		result += ((n / (unsigned int)ft_pow(2, pd)) % 64) * ft_pow(2, pm);
		pd += 6;
		pm -= 8;
	}
	return (result);
}

/*
** Conversion for %lc.
*/

char		*getwcharac(va_list va, int *options)
{
	char		*s;
	wchar_t		c;
	int			bytes;
	int			i;

	c = (wchar_t)(va_arg(va, int));
	bytes = bytesnb(c);
	options[MW] = max(options[MW], bytes);
	if (!(s = malloc(sizeof(*s) * ((long)options[MW] + 1))))
		return (0);
	i = options[LEFT] ? 0 : options[MW] - bytes;
	write_wstr(s + i, &c, bytes);
	fillwc(options[LEFT] ? s + bytes : s, options[MW] - bytes, ' ');
	return (s);
}

/*
** Conversion for %ls.
*/

char		*getwstr(va_list va, int *options)
{
	wchar_t		*arg;
	char		*s;
	int			i;

	arg = va_arg(va, wchar_t*);
	arg = !arg ? (wchar_t*)"(null)" : arg;
	options[ACC] = bytesnb_in_acc(arg, options[ACC]);
	options[MW] = max(options[MW], options[ACC]);
	if (!(s = malloc(sizeof(*s) * ((long)options[MW] + 1))))
		return (0);
	fillwc(s, options[MW], ' ');
	i = options[LEFT] ? 0 : options[MW] - options[ACC];
	write_wstr(s + i, arg, options[ACC]);
	return (s);
}

/*
** Calculates the maximum number of bytes in the string based on accuracy.
*/

int			bytesnb_in_acc(wchar_t *s, int acc)
{
	int		i;
	int		bytes;
	int		len;

	i = 0;
	len = 0;
	if (acc == -1)
		while (s[i])
			len += bytesnb(s[i++]);
	while (s[i] && acc > 0)
	{
		bytes = bytesnb(s[i]);
		acc -= bytes;
		if (acc >= 0)
			len += bytes;
		i++;
	}
	return (len);
}

/*
** Writes a wide char string byte by byte until no accuracy left.
*/

void		write_wstr(char *s, wchar_t *arg, int acc)
{
	int			i;
	int			bytes;
	wchar_t		c;
	int			j;

	i = 0;
	while (acc > 0)
	{
		bytes = bytesnb(*arg);
		c = bytes > 1 ? unicode(*arg, bytes) : *arg;
		j = bytes;
		while (j--)
			s[i + j] = (c / (unsigned int)ft_pow(2, j * 8)) % 256;
		i += bytes;
		arg++;
		acc -= bytes;
	}
}
