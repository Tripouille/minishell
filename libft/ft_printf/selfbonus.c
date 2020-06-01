/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selfbonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:29 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 13:02:32 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*geto(va_list va, int *options)
{
	char				*s;
	unsigned long long	nb;
	t_nbinfos			infos;

	infos.nb = getarg(&nb, va, options, UINT);
	infos.pow = max_pow(nb, 8);
	if ((infos.pow + 1 < options[ACC]) || (nb == 0 && options[ACC]))
		options[SHARP] = 0;
	infos.len = max(infos.pow + 1, options[ACC]);
	if (options[APOS])
		infos.len += infos.pow / 3;
	if (nb == 0 && !options[ACC])
		infos.len = 0;
	infos.len += options[SHARP];
	options[MW] = max(infos.len, options[MW]);
	if (!(s = malloc(sizeof(*s) * ((long)options[MW] + 1))))
		return (0);
	if (options[MW] > infos.len)
		fillwc(s, options[MW], options[ZERO] ? '0' : ' ');
	if (options[SHARP])
		s[options[LEFT] || options[ZERO] ? 0 : options[MW] - infos.len] = '0';
	if (infos.len && !(nb == 0 && options[SHARP]))
		write_integer(s + options[SHARP], &infos, 8, options);
	return (s);
}
