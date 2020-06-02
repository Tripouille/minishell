/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 01:26:25 by jgambard          #+#    #+#             */
/*   Updated: 2020/06/02 16:28:18 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_export(t_lst *args)
{
	char		buffer[100];

	g_status = SUCCESS_STATUS;
	if (!args->next)
		return (builtin_env(args));
	args = args->next;
	while (args)
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
		args = args->next;
	}
}
