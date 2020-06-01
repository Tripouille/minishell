/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:29 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 13:02:32 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_atoi_printf(const char *str)
{
	long	res;
	long	i;

	i = -1;
	res = 0;
	while (ft_isdigit(str[++i]))
	{
		res *= 10;
		res += str[i] - '0';
	}
	return (res);
}

int			max_pow(unsigned long long nb, unsigned long long base)
{
	int						pow;
	unsigned long long		divisor;

	pow = 0;
	divisor = 1;
	while ((nb / base) / divisor)
	{
		divisor *= base;
		pow++;
	}
	return (pow);
}
