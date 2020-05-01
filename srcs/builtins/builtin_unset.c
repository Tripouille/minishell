/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 02:26:52 by jgambard          #+#    #+#             */
/*   Updated: 2020/05/01 19:08:41 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_unset(t_lst *args)
{
	if (!args->next)
	{
		usage_error(get_argc(args, 0), MISSING_ARGUMENT, "");
		status = ERROR_STATUS;
		return ;
	}
	while ((args = args->next))
		del_variable(get_argc(args, 0));
	status = SUCCESS_STATUS;
}
