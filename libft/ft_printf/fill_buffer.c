/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:29 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 13:02:32 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Writes '-', '+' or ' ' before a number.
** The option '+' overrides the option ' '.
*/

void		write_sign(char *s, t_nbinfos *infos, int *options)
{
	s += (options[LEFT] || options[ZERO] ? 0 : options[MW] - infos->len);
	if (infos->neg)
		*s = '-';
	else if (options[PLUS])
		*s = '+';
	else if (options[SPACE])
		*s = ' ';
}

/*
** Writes an integer with thousand separators if options[APOS] (') is set to 1.
*/

void		write_int_w_commas(char *s, t_nbinfos *infos,
								int base, int *options)
{
	unsigned long long		nb;
	int						pos;
	int						commas;

	nb = *(unsigned long long*)(infos->nb);
	pos = 0;
	if (base == 16)
		options[APOS] = 0;
	commas = options[APOS] ? infos->pow / 3 : 0;
	while (infos->pow >= 0)
	{
		if (options[APOS] && pos && !(pos % 3))
			s[infos->pow + commas--] = ',';
		s[infos->pow-- + commas] = nb % base < 10 ?
									nb % base + '0' : nb % base + 'W';
		nb /= base;
		pos++;
	}
}

void		write_basic_number(char *s, unsigned long long nb,
								int base, int pow)
{
	while (pow >= 0)
	{
		s[pow--] = nb % base < 10 ? nb % base + '0' : nb % base + 'W';
		nb /= base;
	}
}

void		write_integer(char *s, t_nbinfos *infos, int base, int *options)
{
	int		i;

	i = options[LEFT] ? 0 : options[MW] - infos->len;
	i += fillwc(s + i, options[ACC] - (infos->pow + 1), '0');
	write_int_w_commas(s + i, infos, base, options);
}

void		write_0x(char *s, t_nbinfos *infos, int *options)
{
	int		i;

	i = options[LEFT] || options[ZERO] ? 0 : options[MW] - infos->len;
	s[i] = '0';
	s[i + 1] = 'x';
}
