/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:09 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 13:02:11 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

/*
** Main function. Start va_list, fills dictionnary with conversions,
** fills list of buffers with text and prints those buffers.
*/

int		ft_dprintf(int fd, const char *s, ...)
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
	dprint_list(fd, begin);
	return (total_size);
}

void	dprint_list(int fd, t_list *begin)
{
	t_list	*tmp;

	while (begin)
	{
		write(fd, begin->b, begin->b_size);
		tmp = begin;
		begin = begin->next;
		free(tmp->b);
		free(tmp);
	}
}
