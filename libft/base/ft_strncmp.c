/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:00:02 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/23 18:37:55 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if ((*s1 || *s2) && (*s1 == *s2 && n && n - 1))
		return (ft_strncmp(++s1, ++s2, --n));
	else
		return (n ? (unsigned char)*s1 - (unsigned char)*s2 : 0);
}
