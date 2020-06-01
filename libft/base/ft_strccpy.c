/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 15:48:18 by aalleman          #+#    #+#             */
/*   Updated: 2020/04/24 15:55:53 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"

void		ft_strccpy(char *dest, char *src, char stop)
{
	while (*src && *src != stop)
		*dest++ = *src++;
	*dest = 0;
}
