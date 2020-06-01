/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 18:55:23 by aalleman          #+#    #+#             */
/*   Updated: 2020/04/26 20:10:30 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"

t_lst	*ft_lst_new(void *content)
{
	t_lst	*node;

	if (!(node = malloc(sizeof(*node))))
		return (0);
	node->content = content;
	node->next = 0;
	return (node);
}
