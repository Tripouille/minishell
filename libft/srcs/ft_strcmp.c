/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:00:02 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/09 07:00:21 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	if ((*s1 || *s2) && *s1 == *s2)
		return (ft_strcmp(++s1, ++s2));
	else
		return ((unsigned char)*s1 - (unsigned char)*s2);
}
