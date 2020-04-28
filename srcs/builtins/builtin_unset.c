/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 02:26:52 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/24 17:19:34 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_unset(char **args)
{
	if (!args[1])
	{
		usage_error(args[0], MISSING_ARGUMENT, "");
		status = ERROR_STATUS;
		return ;
	}
	while (*++args)
		del_variable(*args);
	status = SUCCESS_STATUS;
}
