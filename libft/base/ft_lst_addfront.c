/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_addfront.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 19:06:47 by aalleman          #+#    #+#             */
/*   Updated: 2020/04/26 20:10:21 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"

/*
** Return the added node (so 0 if malloc previously failed).
*/

t_lst		*ft_lst_addfront(t_lst **head, t_lst *new_node)
{
	new_node->next = *head;
	*head = new_node;
	return (new_node);
}
