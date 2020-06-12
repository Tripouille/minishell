/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 01:26:25 by jgambard          #+#    #+#             */
/*   Updated: 2020/06/12 21:15:37 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_variables(void)
{
	char		**variable;
	char		var_name[1000];
	int			i;

	g_status = SUCCESS_STATUS;
	variable = g_env;
	while (*variable)
	{
		i = 0;
		while ((*variable)[i] && (*variable)[i] != '=')
		{
			var_name[i] = (*variable)[i];
			i++;
		}
		var_name[i] = 0;
		ft_printf("declare -x %s=\"%s\"\n", var_name,
					get_variable_value(var_name));
		variable++;
	}
}

void	builtin_export(t_lst *args)
{
	char		buffer[1000];

	g_status = SUCCESS_STATUS;
	if (!args->next)
		return (show_variables());
	while ((args = args->next))
	{
		if (get_arg_value(args, 0)[0] == '=')
			minishell_error("bad assignment", "", 1);
		else if (!is_identifier(get_arg_value(args, 0)))
		{
			ft_strccpy(buffer, get_arg_value(args, 0), '=');
			usage_error("export", "not an identifier", buffer, 1);
		}
		else
			set_variable(get_arg_value(args, 0));
	}
}
