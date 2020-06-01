/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strccmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 18:07:24 by aalleman          #+#    #+#             */
/*   Updated: 2020/04/23 18:27:34 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"

int		ft_strccmp(const char *s1, const char *s2, char c)
{
	if ((*s1 || *s2) && *s1 == *s2 && *s1 != c && *s2 != c)
		return (ft_strccmp(++s1, ++s2, c));
	else
		return ((unsigned char)*s1 - (unsigned char)*s2);
}
