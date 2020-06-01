/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:00:02 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/23 18:37:55 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int		dl;
	unsigned int		sl;

	dl = 0;
	while (dest[dl])
		dl++;
	sl = 0;
	while (size > 1 && src[sl] && (dl + sl < size - 1))
	{
		dest[dl + sl] = src[sl];
		sl++;
	}
	if (dl < size - 1)
		dest[dl + sl] = 0;
	if (size && dl > size)
		dl = size;
	while (src[sl])
		sl++;
	return (size ? sl + dl : sl);
}
