/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:29 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 13:02:32 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Conversion for %n.
** Retrieves total_size (number of written characters)
** in the variable pointed by the argument.
*/

char	*setn(va_list va, int *options)
{
	void	*p;

	if (!(p = va_arg(va, void*)))
		return (malloc(sizeof(char)));
	if (options[LM] == 0)
		*(int*)p = options[TOTAL_SIZE];
	else if (options[LM] == HH)
		*(char*)p = options[TOTAL_SIZE];
	else if (options[LM] == H)
		*(short int*)p = options[TOTAL_SIZE];
	else if (options[LM] == L)
		*(long*)p = options[TOTAL_SIZE];
	else if (options[LM] == LL)
		*(long long*)p = options[TOTAL_SIZE];
	return (malloc(sizeof(char)));
}
