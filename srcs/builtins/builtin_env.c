/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 01:06:39 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/24 13:17:23 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_env(char **args)
{
	char		**variable;

	if (args[1])
	{
		ft_dprintf(2, "%s: %s: %s\n", args[0], args[1], UNKNOWN_PARAMETER);
		status = ERROR_STATUS;
		return ;
	}
	variable = env;
	while (*variable)
		ft_printf("%s\n", *variable++);
	status = SUCCESS_STATUS;
}
