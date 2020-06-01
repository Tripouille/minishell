/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:29 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 13:02:32 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Conversion for %f.
** Accuracy (6 by default) is the minimum number of digits in decimal part.
*/

char	*getf(va_list va, int *options)
{
	char			*s;
	long double		nb;
	t_bool			sign;
	t_nbinfos		infos;

	nb = va_arg(va, double);
	if (ft_isnan(&s, nb, &infos, options))
		return (s);
	infos.nb = &nb;
	infos.neg = is_neg(nb);
	sign = infos.neg || options[SPACE] || options[PLUS] ? 1 : 0;
	nb = abs2(nb);
	options[ACC] = options[ACC] < 0 ? 6 : options[ACC];
	nb = dround(nb, options[ACC]);
	infos.pow = max_dpow(nb);
	infos.len = sign + max(infos.pow + 1, 1);
	infos.len += (options[ACC] || options[SHARP] ? 1 : 0) + options[ACC];
	infos.len += options[APOS] && infos.pow > 0 ? infos.pow / 3 : 0;
	if (!(s = mallouc_double(&infos, options)))
		return (0);
	write_sign(s, &infos, options);
	write_f(s + sign, &infos, options);
	return (s);
}

/*
** Conversion for %e, scientific notation (example 2.01500e-03).
** Accuracy (6 by default) is the minimum number of digits in decimal part.
*/

char	*gete(va_list va, int *options)
{
	char				*s;
	long double			nb;
	t_bool				sign;
	t_nbinfos			infos;

	nb = va_arg(va, double);
	if (ft_isnan(&s, nb, &infos, options))
		return (s);
	infos.nb = &nb;
	infos.neg = is_neg(nb);
	sign = infos.neg || options[SPACE] || options[PLUS] ? 1 : 0;
	nb = abs2(nb);
	options[ACC] = options[ACC] < 0 ? 6 : options[ACC];
	nb = dround(nb, options[ACC] - max_dpow(nb));
	infos.pow = max_dpow(nb);
	infos.len = max_dpow(abs2(infos.pow)) + 1;
	infos.len = sign + max(infos.len, 2);
	infos.len += (options[ACC] || options[SHARP] ? 1 : 0) + options[ACC] + 3;
	if (!(s = mallouc_double(&infos, options)))
		return (0);
	write_sign(s, &infos, options);
	write_e(s + sign, &infos, options);
	return (s);
}

/*
** Conversion for %g.
** Accuracy is minimum 1.
*/

char	*getg(va_list va, int *options)
{
	char			*s;
	double			nb;
	t_nbinfos		infos;

	nb = va_arg(va, double);
	if (ft_isnan(&s, nb, &infos, options))
		return (s);
	infos.nb = &nb;
	infos.neg = is_neg(nb);
	nb = abs2(nb);
	options[ACC] = options[ACC] < 0 ? 6 : options[ACC];
	if (!options[ACC])
		options[ACC] = 1;
	infos.pow = max_dpow(nb);
	if (infos.pow < -4 || infos.pow >= options[ACC])
		getge(&s, &infos, options);
	else
		getgf(&s, &infos, options);
	return (s);
}

/*
** Conversion for %g in both cases.
** Accuracy is the number of significant digits.
** Useless zeros at the end of the number are removed.
*/

void	getgf(char **s, t_nbinfos *infos, int *options)
{
	long double		nb;
	t_bool			sign;

	nb = *(double*)infos->nb;
	sign = infos->neg || options[SPACE] || options[PLUS] ? 1 : 0;
	nb = dround(nb, options[ACC] + (nb < 1 ? -infos->pow - 1 : 0));
	infos->pow = max_dpow(nb);
	if (!options[SHARP])
		options[ACC] -= useless_zero_nb(nb, options[ACC], 'f');
	infos->len = sign;
	options[ACC] += max(-infos->pow, 0);
	infos->len += options[ACC];
	infos->len += infos->pow + 1 < options[ACC] || options[SHARP] ? 1 : 0;
	infos->len += options[APOS] && infos->pow > 0 ? infos->pow / 3 : 0;
	if (!(*s = mallouc_double(infos, options)))
		return ;
	write_sign(*s, infos, options);
	infos->nb = &nb;
	options[ACC] -= max(infos->pow + 1, 1);
	write_f(*s + sign, infos, options);
}

void	getge(char **s, t_nbinfos *infos, int *options)
{
	long double		nb;
	t_bool			sign;

	options[ACC]--;
	nb = *(double*)infos->nb;
	sign = infos->neg || options[SPACE] || options[PLUS] ? 1 : 0;
	nb = dround(nb, options[ACC] - infos->pow);
	infos->pow = max_dpow(nb);
	if (!options[SHARP])
		options[ACC] -= useless_zero_nb(nb, options[ACC], 'e');
	infos->len = max_dpow(abs2(infos->pow)) + 1;
	infos->len = sign + max(infos->len, 2);
	infos->len += (options[ACC] || options[SHARP] ? 1 : 0) + options[ACC] + 3;
	if (!(*s = mallouc_double(infos, options)))
		return ;
	write_sign(*s, infos, options);
	infos->nb = &nb;
	write_e(*s + sign, infos, options);
}
