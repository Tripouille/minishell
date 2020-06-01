/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_numbers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:29 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 13:02:32 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Conversion for %d and %i.
** Accuracy is the minimum number of digits (eventually fills with 0 at front).
** With number 0 and accuracy 0, nothing is printed.
*/

char		*geti(va_list va, int *options)
{
	char		*s;
	long long	nb;
	t_bool		sign;
	t_nbinfos	infos;

	infos.nb = getarg(&nb, va, options, INT);
	infos.neg = is_neg(nb);
	sign = infos.neg || options[SPACE] || options[PLUS] ? 1 : 0;
	nb = abs2(nb);
	infos.pow = max_pow(nb, 10);
	infos.len = sign + max(infos.pow + 1, options[ACC]);
	if (options[APOS])
		infos.len += infos.pow / 3;
	if (!nb && !options[ACC])
		infos.len = sign;
	options[MW] = max(infos.len, options[MW]);
	if (!(s = malloc(sizeof(*s) * ((long)options[MW] + 1))))
		return (0);
	if (options[MW] > infos.len)
		fillwc(s, options[MW], options[ZERO] ? '0' : ' ');
	write_sign(s, &infos, options);
	if (infos.len > sign)
		write_integer(s + sign, &infos, 10, options);
	return (s);
}

/*
** Conversion for %u (same as %i with unsigned int).
*/

char		*getu(va_list va, int *options)
{
	char				*s;
	unsigned long long	nb;
	t_nbinfos			infos;

	infos.nb = getarg(&nb, va, options, UINT);
	infos.pow = max_pow(nb, 10);
	infos.len = max(infos.pow + 1, options[ACC]);
	if (options[APOS])
		infos.len += infos.pow / 3;
	if (!nb && !options[ACC])
		infos.len = 0;
	options[MW] = max(infos.len, options[MW]);
	if (!(s = malloc(sizeof(*s) * ((long)options[MW] + 1))))
		return (0);
	if (options[MW] > infos.len)
		fillwc(s, options[MW], options[ZERO] ? '0' : ' ');
	if (infos.len)
		write_integer(s, &infos, 10, options);
	return (s);
}

/*
** Conversion for %x.
*/

char		*getx(va_list va, int *options)
{
	char				*s;
	unsigned long long	nb;
	int					prefix;
	t_nbinfos			infos;

	infos.nb = getarg(&nb, va, options, UINT);
	infos.pow = max_pow(nb, 16);
	infos.len = max(infos.pow + 1, options[ACC]);
	prefix = nb && options[SHARP] ? 2 : 0;
	infos.len += prefix;
	if (!nb && !options[ACC])
		infos.len = 0;
	options[MW] = max(infos.len, options[MW]);
	if (!(s = malloc(sizeof(*s) * ((long)options[MW] + 1))))
		return (0);
	if (options[MW] > infos.len)
		fillwc(s, options[MW], options[ZERO] ? '0' : ' ');
	if (nb && options[SHARP])
		write_0x(s, &infos, options);
	if (infos.len)
		write_integer(s + prefix, &infos, 16, options);
	return (s);
}

/*
** Conversion for %X.
*/

char		*getux(va_list va, int *options)
{
	return (ft_toupper(getx(va, options)));
}

/*
** Conversion for %p. Needs 2 more spaces for "0x".
*/

char		*getp(va_list va, int *options)
{
	char			*s;
	unsigned long	nb;
	t_nbinfos		infos;

	nb = va_arg(va, unsigned long);
	infos.nb = &nb;
	infos.pow = max_pow(nb, 16);
	infos.len = infos.pow + 3;
	options[MW] = max(infos.len, options[MW]);
	if (!(s = malloc(sizeof(*s) * ((long)options[MW] + 1))))
		return (0);
	if (options[MW] > infos.len)
		fillwc(s, options[MW], ' ');
	write_0x(s, &infos, options);
	write_basic_number(s + (options[LEFT] ? 0 : options[MW] - infos.len) + 2,
	nb, 16, infos.pow);
	return (s);
}
