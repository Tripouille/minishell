/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:52 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 13:02:54 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Main function. Fills line and returns 1 (or 0 on EOF or -1 on error).
*/

int					get_next_line(int fd, char **line)
{
	static t_fd_list	*begin = 0;
	int					nl;

	if (!set_fd_list(fd, &begin))
		return (remove_fd(&begin, 1));
	if (begin->b_list->start > 0)
	{
		nl = delta_to_nl(begin->b_list);
		if (nl != -1 || str_len(begin->b_list->b) < BUFFER_SIZE)
			return (fill_line(line, nl, &begin));
		if (!add_b_list(begin))
			return (remove_fd(&begin, 1));
	}
	if (fill_buffers(fd, &begin) == -1)
		return (-1);
	return (fill_line(line, delta_to_nl(begin->b_list), &begin));
}

/*
** Puts the correct fd list as first element of the fd lists
** and sets begin on it.
*/

int					set_fd_list(int fd, t_fd_list **begin)
{
	t_fd_list	*tmp;
	t_fd_list	*prev;

	prev = 0;
	tmp = *begin;
	while (tmp && tmp->fd != fd)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		if (!(tmp = new_fd_list(fd)))
			return (0);
		tmp->next = *begin;
		*begin = tmp;
	}
	else if (tmp != *begin)
	{
		if (prev)
			prev->next = tmp->next;
		tmp->next = *begin;
		*begin = tmp;
	}
	return (1);
}

/*
** Reads and fills buffers until new line or EOF.
** Cleans fd list if reads -1.
*/

int					fill_buffers(int fd, t_fd_list **begin)
{
	int			ret;
	int			nl;

	while ((ret = read(fd, (*begin)->b_list->b, BUFFER_SIZE)) == BUFFER_SIZE
	&& ret && (nl = delta_to_nl((*begin)->b_list)) == -1)
	{
		(*begin)->b_list->b[ret] = '\0';
		if (!add_b_list(*begin))
			return (remove_fd(begin, 1));
	}
	if (ret < 0)
	{
		remove_fd(begin, 0);
		return (-1);
	}
	(*begin)->b_list->b[ret] = '\0';
	return (1);
}

/*
** Mallocs line and copies the buffers in line until new line or EOF.
*/

int					fill_line(char **line, int nl, t_fd_list **begin)
{
	int			len;
	int			size;
	t_b_list	*b_list;
	t_b_list	*tmp;

	if ((size = malloc_line(line, nl, begin)) == -1)
		return (remove_fd(begin, 1));
	b_list = (*begin)->b_list;
	len = nl == -1 ? str_len(b_list->b + b_list->start) : nl;
	while (b_list)
	{
		while (len)
			(*line)[--size] = b_list->b[b_list->start + --len];
		tmp = b_list->next;
		if (b_list != (*begin)->b_list)
			free(b_list);
		b_list = tmp;
		if (b_list)
			len = str_len(b_list->b + b_list->start);
	}
	(*begin)->b_list->next = 0;
	(*begin)->b_list->start += nl + 1;
	return (nl == -1 ? remove_fd(begin, 0) : 1);
}

/*
** Calculates length of line and mallocs it.
*/

int					malloc_line(char **line, int nl, t_fd_list **begin)
{
	int			size;
	t_b_list	*b_list;

	b_list = (*begin)->b_list;
	size = nl != -1 ? nl : str_len(b_list->b + b_list->start);
	while ((b_list = b_list->next))
		size += str_len(b_list->b + b_list->start);
	if (!(*line = malloc(sizeof(**line) * (size + 1))))
		return (-1);
	(*line)[size] = 0;
	return (size);
}
