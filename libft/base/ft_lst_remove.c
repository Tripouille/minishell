/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 03:01:41 by aalleman          #+#    #+#             */
/*   Updated: 2020/05/17 07:22:28 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"

void	ft_lst_remove(t_lst **head, t_lst *needle, void (*del)(void*))
{
	if (*head == needle)
	{
		*head = (*head)->next;
		if (del)
			del(needle->content);
		free(needle);
	}
	else if ((*head)->next)
		ft_lst_remove(&((*head)->next), needle, del);
}
