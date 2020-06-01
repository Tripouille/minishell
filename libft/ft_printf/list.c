/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:29 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 13:02:32 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Adds a buffer to the back of the list with its size.
*/

int		list_add(t_list **begin, void *s, int size)
{
	static t_list	*last = 0;
	t_list			*new;

	if (!last)
		last = *begin;
	if (!(new = malloc(sizeof(*new))))
		return (0);
	new->b = s;
	new->b_size = size;
	new->next = 0;
	if (!*begin)
		*begin = new;
	else
		last->next = new;
	last = new;
	return (1);
}

/*
** Frees the buffers list.
*/

int		list_clear(t_list **begin)
{
	if (!*begin)
		return (-1);
	list_clear(&((*begin)->next));
	free((*begin)->b);
	free(*begin);
	*begin = 0;
	return (-1);
}

/*
** Reads format, converts if needed
** and adds the retrieved string to the buffers list.
** Size is added to TOTAL_SIZE at each conversion
** to be used for n conversion and to be returned in ft_printf.
*/

int		fill_list(t_list **begin, char *s, va_list va, t_dict *dict)
{
	void	*buffer;
	int		options[OPTIONS_NB];

	options[TOTAL_SIZE] = 0;
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			if (!*s)
				return (options[TOTAL_SIZE]);
			if (!(buffer = convertarg(&s, va, dict, options)))
				return (list_clear(begin));
		}
		else if (!(buffer = collectchars(&s, options + MW)))
			return (list_clear(begin));
		options[TOTAL_SIZE] += options[MW];
		if (!list_add(begin, buffer, options[MW]))
		{
			free(buffer);
			return (list_clear(begin));
		}
	}
	return (options[TOTAL_SIZE]);
}

/*
** Prints buffers and frees list.
*/

void	print_list(t_list *begin)
{
	t_list	*tmp;

	while (begin)
	{
		write(1, begin->b, begin->b_size);
		tmp = begin;
		begin = begin->next;
		free(tmp->b);
		free(tmp);
	}
}
