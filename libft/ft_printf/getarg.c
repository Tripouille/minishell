/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getarg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:29 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 13:02:32 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Resizes the argument according to the length modifier.
*/

void		*getarg(void *nb, va_list va, int *options, int size)
{
	size += options[LM];
	if (size == CHAR)
		*(long long*)nb = (char)va_arg(va, int);
	else if (size == SINT)
		*(long long*)nb = (short int)va_arg(va, int);
	else if (size == INT)
		*(long long*)nb = va_arg(va, int);
	else if (size == LONG)
		*(long long*)nb = va_arg(va, long);
	else if (size == LLONG)
		*(long long*)nb = va_arg(va, long long);
	else if (size == UCHAR)
		*(unsigned long long*)nb = (unsigned char)va_arg(va, unsigned int);
	else if (size == USINT)
		*(unsigned long long*)nb = (unsigned short int)va_arg(va, unsigned int);
	else if (size == UINT)
		*(unsigned long long*)nb = va_arg(va, unsigned int);
	else if (size == ULONG)
		*(unsigned long long*)nb = va_arg(va, unsigned long);
	else if (size == ULLONG)
		*(unsigned long long*)nb = va_arg(va, unsigned long long);
	return (nb);
}
