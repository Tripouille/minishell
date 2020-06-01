/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:29 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 13:02:32 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Returns the maximum power of 10 (possibly negative) in a number.
*/

int				max_dpow(double nb)
{
	int			pow;
	double		divisor;

	pow = 0;
	divisor = 1;
	if (nb >= 1)
		while ((nb / 10) / divisor >= 1)
		{
			divisor *= 10;
			pow++;
		}
	else if (nb)
		while ((nb * 10) * divisor < 10)
		{
			divisor *= 10;
			pow--;
		}
	return (pow);
}

long double		ft_pow(long double nb, int pow)
{
	double		result;

	result = 1;
	if (pow >= 0)
		while (pow-- > 0)
			result *= nb;
	else
		while (pow++ < 0)
			result /= nb;
	return (result);
}

/*
** Rounds the number according to its decimal accuracy.
*/

long double		dround(long double d, int acc)
{
	long double		dcopy;
	long double		next;
	int				i;

	dcopy = d;
	i = acc;
	while (dcopy >= 10)
	{
		dcopy /= 10;
		i++;
	}
	while (i-- > 0)
	{
		dcopy -= (int)dcopy;
		dcopy *= 10;
	}
	next = (dcopy - (int)dcopy) * 10;
	if (next > 5.0 || (next == 5.0 && (int)dcopy % 2))
		return (d + ft_pow(10, -(acc + 1)) * (10 - (int)next));
	else
		return (d);
}

/*
** Formats the number to 0.xxxx.
** For f case, adds number of zeros right after the decimal point if power < 0
** or removes number of digits in integer part to accuracy.
*/

int				useless_zero_nb(long double nb, int acc, char type)
{
	int		pow;

	if (type == 'f')
	{
		pow = max_dpow(nb);
		if (pow < 0)
			acc += -pow - 1;
		while (pow >= 0)
		{
			acc--;
			nb -= (int)(nb / ft_pow(10, pow)) * ft_pow(10, pow);
			pow--;
		}
	}
	else if (type == 'e')
	{
		while (nb >= 10)
			nb /= 10;
		while (nb && nb < 1)
			nb *= 10;
		nb -= (int)nb;
	}
	return (count_useless_zeros(nb, acc));
}

int				count_useless_zeros(long double nb, int acc)
{
	int		count;

	count = 0;
	while (acc-- > 0)
	{
		nb *= 10;
		if (!(int)nb)
			count++;
		else
			count = 0;
		nb -= (int)nb;
	}
	return (count);
}
