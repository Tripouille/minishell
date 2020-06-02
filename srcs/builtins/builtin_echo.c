/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:41:59 by jgambard          #+#    #+#             */
/*   Updated: 2020/06/02 16:29:04 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Check if -n to display arguments
** with newline at the end or not.
*/

void		builtin_echo(t_lst *args)
{
	int		newline;

	g_status = SUCCESS_STATUS;
	args = args->next;
	newline = 1;
	if (args)
		newline = ft_strcmp("-n", get_arg_value(args, 0));
	if (!newline)
		args = args->next;
	while (args)
	{
		write(1, get_arg_value(args, 0), ft_strlen(get_arg_value(args, 0)));
		args = args->next;
		if (args)
			write(1, " ", 1);
	}
	if (newline)
		write(1, "\n", 1);
}
