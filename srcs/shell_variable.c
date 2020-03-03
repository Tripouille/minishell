/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 00:06:44 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/03 02:16:32 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				del_all_variables(void)
{
	t_shell_variable		*del;

	while (shell_variables)
	{
		del = shell_variables;
		shell_variables = shell_variables->next;
		free(del->name);
		free(del->value);
		free(del);
	}
}

t_shell_variable	*get_variable(char *name)
{
	t_shell_variable	*variable;

	variable = shell_variables;
	while (variable && ft_strcmp(name, variable->name))
		variable = variable->next;
	return (variable);
}

char				*get_variable_value(char *name)
{
	t_shell_variable	*variable;

	variable = shell_variables;
	while (variable && ft_strcmp(name, variable->name))
		variable = variable->next;
	return (variable ? variable->value : 0);
}

void				add_variable(char *name, char *value, t_bool exported)
{
	t_shell_variable	*new_variable;

	if (!(new_variable = malloc(sizeof(t_shell_variable))))
		error_exit("Malloc fail");
	new_variable->name = name;
	new_variable->value = value;
	new_variable->exported = exported;
	new_variable->next = shell_variables;
	shell_variables = new_variable;
}
