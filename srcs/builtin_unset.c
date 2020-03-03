/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 02:26:52 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/03 04:38:43 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_variable(char *name)
{
	t_shell_variable	*variable;
	t_shell_variable	**pointer_on_pointer_on_variable;

	variable = shell_variables;
	pointer_on_pointer_on_variable = &shell_variables;
	while (variable && ft_strcmp(name, variable->name))
	{
		pointer_on_pointer_on_variable = &variable->next;
		variable = variable->next;
	}
	if (variable)
	{
		*pointer_on_pointer_on_variable = variable->next;
		free(variable->name);
		free(variable->value);
		free(variable);
	}
}


void		builtin_unset(char **args)
{
	while (*++args)
		unset_variable(*args);
}
