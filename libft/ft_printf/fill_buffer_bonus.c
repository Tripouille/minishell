/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_buffer_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:29 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 13:02:32 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Used for %f conversion, and %g conversion in f case.
** For each digit in the integer part, writes it then removes it.
** Extracts digits in the decimal part by shifting them to the integer part.
*/

void		write_f(char *s, t_nbinfos *infos, int *options)
{
	int				i;
	long double		nb;
	int				commas;
	int				maxpow;

	nb = *(long double*)infos->nb;
	commas = 0;
	i = options[LEFT] ? 0 : options[MW] - infos->len;
	infos->pow = max(infos->pow, 0);
	maxpow = infos->pow;
	while (infos->pow >= 0)
	{
		if (options[APOS] && !((maxpow + 1 - i) % 3) && maxpow != infos->pow)
			s[i + commas++] = ',';
		s[i + commas] = nb / ft_pow(10, infos->pow) + '0';
		nb -= (s[i++ + commas] - '0') * ft_pow(10, infos->pow--);
	}
	if (options[ACC] || options[SHARP])
		s[i++ + commas] = '.';
	while (options[ACC]--)
	{
		nb *= 10;
		s[i++ + commas] = nb + '0';
		nb -= (int)nb;
	}
}

/*
** Used for %e conversion, and %g conversion in e case.
** First sets the number to one digit in integer part.
** Writes the integer part, the decimal part and the exponent.
*/

void		write_e(char *s, t_nbinfos *infos, int *options)
{
	int				pow_len;
	int				i;
	long double		nb;

	nb = *(long double*)infos->nb;
	i = options[LEFT] ? 0 : options[MW] - infos->len;
	while (nb >= 10)
		nb /= 10;
	while (nb && nb < 1)
		nb *= 10;
	s[i++] = (int)nb + '0';
	if (options[ACC] || options[SHARP])
		s[i++] = '.';
	while (options[ACC]--)
	{
		nb -= (int)nb;
		nb *= 10;
		s[i++] = (int)nb + '0';
	}
	s[i++] = 'e';
	s[i++] = infos->pow < 0 ? '-' : '+';
	pow_len = max_dpow(abs2(infos->pow));
	write_basic_number(s + i, abs2(infos->pow), 10, max(pow_len, 1));
}

char		*mallouc_double(t_nbinfos *infos, int *options)
{
	char	*s;

	options[MW] = max(infos->len, options[MW]);
	if (!(s = malloc(sizeof(*s) * ((long)options[MW] + 1))))
		return (0);
	if (options[MW] > infos->len)
		fillwc(s, options[MW], options[ZERO] ? '0' : ' ');
	return (s);
}

int			ft_isnan(char **s, long double nb, t_nbinfos *infos, int *options)
{
	if (nb == 1.0 / 0.0 || nb == -1.0 / 0.0 || nb != nb)
		options[ZERO] = 0;
	infos->len = 3;
	if (nb != nb)
	{
		if (!(*s = mallouc_double(infos, options)))
			return (-1);
		ft_strncpy(*s + (options[LEFT] ? 0 : options[MW] - 3), "nan", 3);
	}
	else if (nb == 1.0 / 0.0)
	{
		if (!(*s = mallouc_double(infos, options)))
			return (-1);
		ft_strncpy(*s + (options[LEFT] ? 0 : options[MW] - 3), "inf", 3);
	}
	else if (nb == -1.0 / 0.0)
	{
		infos->len++;
		if (!(*s = mallouc_double(infos, options)))
			return (-1);
		ft_strncpy(*s + (options[LEFT] ? 0 : options[MW] - 4), "-inf", 4);
	}
	else
		return (0);
	return (1);
}
