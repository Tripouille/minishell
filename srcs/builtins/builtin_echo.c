/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:41:59 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/04 03:21:41 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_echo(char **args)
{
	int		newline;

	args++;
	newline = *args && ft_strcmp("-n", *args);
	if (!newline)
		args++;
	while (*args)
	{
		write(1, *args, slen(*args));
		args++;
		if (*args)
			write(1, " ", 1);
	}
	if (newline)
		write(1, "\n", 1);
}
