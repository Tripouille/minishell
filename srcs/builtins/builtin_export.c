/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 01:26:25 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/06 04:08:29 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_variable(char *arg)
{
	int					i;
	t_shell_variable	*variable;

	i = 0;
	while (arg[i] != '=')
		i++;
	arg[i] = 0;
	if ((variable = get_variable(arg)))
	{
		free(variable->value);
		variable->value = ft_strdup(arg + i + 1);
	}
	else
		//add_variable(ft_strdup(arg), ft_strdup(arg + i + 1), NOT_EXPORTED);
		;
}

void	export_variable(char *name)
{
	t_shell_variable	*variable;

	if ((variable = get_variable(name)))
		variable->exported = EXPORTED;
}

void	builtin_export(char **args)
{
	if (!args[1])
		return (builtin_env(args));
	while (*++args)
	{
		if (cinstr('=', *args) != -1)
			assign_variable(*args);
		export_variable(*args);
	}
}
