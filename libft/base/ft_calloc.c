/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:00:02 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/23 18:37:55 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t		total_size;
	size_t		i;
	char		*ptr;

	total_size = count * size;
	i = -1;
	if (!(ptr = malloc(total_size)))
		return (0);
	while (++i < total_size)
		ptr[i] = 0;
	return (ptr);
}
