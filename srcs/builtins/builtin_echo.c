/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:41:59 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/23 18:37:55 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Check if 2nd argument is -n to display 2nd argument
** and newline at the end or not.
*/

void		builtin_echo(char **args)
{
	int		newline;

	args++;
	if (!*args)
	{
		write(1, "\n", 1);
		return ;
	}
	newline = ft_strcmp("-n", *args);
	if (!newline)
		args++;
	while (*args)
	{
		write(1, *args, ft_strlen(*args));
		args++;
		if (*args)
			write(1, " ", 1);
	}
	if (newline)
		write(1, "\n", 1);
	status = SUCCESS_STATUS;
}
