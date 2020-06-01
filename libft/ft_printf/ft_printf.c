/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:29 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 13:02:32 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Main function. Start va_list, fills dictionnary with conversions,
** fills list of buffers with text and prints those buffers.
*/

int		ft_printf(const char *s, ...)
{
	va_list		va;
	t_list		*begin;
	t_dict		dict[15];
	int			total_size;

	va_start(va, s);
	begin = 0;
	initdict(dict);
	total_size = fill_list(&begin, (char*)s, va, dict);
	va_end(va);
	print_list(begin);
	return (total_size);
}
