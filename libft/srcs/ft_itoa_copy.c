/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 01:51:38 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/10 02:18:51 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
