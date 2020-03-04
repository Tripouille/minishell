/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 01:06:39 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/04 04:11:27 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_env(char **args)
{
	t_shell_variable		*variable;

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
	variable = shell_variables;
	while (variable)
	{
		if (variable->exported)
		{
			write(1, variable->name, slen(variable->name));
			write(1, "=", 1);
			write(1, variable->value, slen(variable->value));
			write(1, "\n", 1);
		}
		variable = variable->next;
	}
}
