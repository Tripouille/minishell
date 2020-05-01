/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 01:26:25 by jgambard          #+#    #+#             */
/*   Updated: 2020/05/01 19:05:01 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_export(t_lst *args)
{
	char		buffer[100];
	
	if (!args->next)
		return (builtin_env(args));
	args = args->next;
	while (args)
	{
		if (get_argc(args, 0)[0] == '=')
			minishell_error("bad assignment", "");
		else if (!is_identifier(get_argc(args, 0)))
		{
			ft_strccpy(buffer, get_argc(args, 0), '=');
			usage_error("export", "not an identifier", buffer);
		}
		else
			set_variable(get_argc(args, 0));
		args = args->next;
	}
	status = SUCCESS_STATUS;
}
