/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:29 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 13:02:32 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

double		abs2(double x)
{
	return (x < 0 ? -x : x);
}

double		max(double a, double b)
{
	return (a > b ? a : b);
}

double		min(double a, double b)
{
	return (a < b ? a : b);
}

double		is_neg(double x)
{
	return (x < 0 ? 1 : 0);
}
