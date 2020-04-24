/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:41:59 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/24 12:49:03 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Check if -n to display arguments
** with newline at the end or not.
*/

void		builtin_echo(char **args)
{
	int		newline;

	args++;
	newline = 1;
	if (*args)
		newline = ft_strcmp("-n", *args);
	if (!newline)
		args++;
	while (*args)
	{
		write(1, *args, ft_strlen(*args));
		if (*++args)
			write(1, " ", 1);
	}
	if (newline)
		write(1, "\n", 1);
	status = SUCCESS_STATUS;
}
