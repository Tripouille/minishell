/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 01:06:39 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/06 03:18:17 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_env(char **args)
{
	char		**variable;

	if (args[1])
	{
		write(2, args[0], slen(args[0]));
		write(2, ": ", 2);
		write(2, args[1], slen(args[1]));
		write(2, ": ", 2);
		write(2, UNKNOWN_PARAMETER, slen(UNKNOWN_PARAMETER));
		write(2, "\n", 1);
		return ;
	}
	variable = env;
	while (*variable)
	{
		write(1, *variable, slen(*variable));
		write(1, "\n", 1);
		variable++;
	}
}
