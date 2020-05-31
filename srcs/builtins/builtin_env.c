/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 01:06:39 by jgambard          #+#    #+#             */
/*   Updated: 2020/05/31 13:10:16 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_env(t_lst *args)
{
	char		**variable;

	if (args->next)
	{
		ft_dprintf(2, "%s: %s: %s\n", get_arg_value(args, 0),
					get_arg_value(args, 1), UNKNOWN_PARAMETER);
		g_status = ERROR_STATUS;
		return ;
	}
	variable = g_env;
	while (*variable)
		ft_printf("%s\n", *variable++);
	g_status = SUCCESS_STATUS;
}
