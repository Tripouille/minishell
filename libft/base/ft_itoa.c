/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 02:19:02 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/23 18:37:55 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"

static int		ft_mallocitoa(char **res, long n)
{
	int		bytes;
	int		is_neg;

	bytes = 1;
	is_neg = 0;
	if (n < 0)
		bytes++;
	if (n < 0)
		is_neg = 1;
	while ((n /= 10))
		bytes++;
	*res = malloc(sizeof(**res) * (bytes + 1));
	if (*res && is_neg)
		**res = '-';
	return (bytes);
}

char			*ft_itoa(long n)
{
	int		bytes;
	char	*res;

	bytes = ft_mallocitoa(&res, n);
	if (!res)
		return (0);
	res[bytes] = 0;
	if (n == 0)
		res[0] = '0';
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		bytes--;
		res[bytes] = n % 10 + '0';
		n /= 10;
	}
	return (res);
}
