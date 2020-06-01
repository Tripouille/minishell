/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_copy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 16:16:40 by user42            #+#    #+#             */
/*   Updated: 2020/04/23 16:17:44 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"

static int		count_bytes(long n)
{
	int		bytes;

	bytes = 1;
	if (n < 0)
		bytes++;
	while ((n /= 10))
		bytes++;
	return (bytes);
}

char			*ft_itoa_copy(char *buffer, long n)
{
	int		bytes;

	bytes = count_bytes(n);
	buffer[bytes] = 0;
	if (n == 0)
		buffer[0] = '0';
	else if (n < 0)
	{
		n *= -1;
		buffer[0] = '-';
	}
	while (n > 0)
	{
		bytes--;
		buffer[bytes] = n % 10 + '0';
		n /= 10;
	}
	return (buffer);
}
