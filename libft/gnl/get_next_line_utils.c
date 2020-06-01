/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:52 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 13:02:54 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Creates a new fd_list element associated to the given fd,
** then assigns its b_list to a new element.
*/

t_fd_list			*new_fd_list(int fd)
{
	t_fd_list		*new;

	if (!(new = malloc(sizeof(*new))))
		return (NULL);
	new->fd = fd;
	new->next = NULL;
	new->b_list = NULL;
	if (!(add_b_list(new)))
	{
		free(new);
		return (NULL);
	}
	return (new);
}

/*
** Adds a new b_list element on front with an empty buffer.
*/

int					add_b_list(t_fd_list *fd_list)
{
	t_b_list	*new;

	if (!(new = malloc(sizeof(*new))))
		return (0);
	new->b[0] = '\0';
	new->start = 0;
	new->next = fd_list->b_list;
	fd_list->b_list = new;
	return (1);
}

/*
** Removes the current fd and all its b_list elements from the list
** or (if all = 1) removes all fds and their b_lists elements.
*/

int					remove_fd(t_fd_list **begin, int all)
{
	t_fd_list	*tmp_fd;
	t_b_list	*tmp_b;

	if (!*begin)
		return (-1);
	if (all)
		remove_fd(&(*begin)->next, 1);
	while ((*begin)->b_list)
	{
		tmp_b = (*begin)->b_list;
		(*begin)->b_list = (*begin)->b_list->next;
		free(tmp_b);
	}
	tmp_fd = *begin;
	*begin = (*begin)->next;
	free(tmp_fd);
	return (all ? -1 : 0);
}

/*
** Returns the delta from start to the next new line (or -1 if no new line);
*/

int					delta_to_nl(t_b_list *b_list)
{
	int		i;

	i = 0;
	while (b_list->b[b_list->start + i]
	&& b_list->b[b_list->start + i] != '\n')
		i++;
	return (b_list->b[b_list->start + i] == '\n' ? i : -1);
}

int					str_len(const char *str)
{
	int		len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}
