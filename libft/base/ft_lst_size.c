/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 19:14:51 by aalleman          #+#    #+#             */
/*   Updated: 2020/04/26 20:10:52 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"

int		ft_lst_size(t_lst *node)
{
	int		count;

	count = 0;
	while (node)
	{
		count++;
		node = node->next;
	}
	return (count);
}
