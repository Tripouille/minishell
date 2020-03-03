/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 01:06:39 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/03 01:42:56 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_env(__attribute__((unused)) char **args)
{
	t_shell_variable		*variable;

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
