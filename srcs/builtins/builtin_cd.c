/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 04:31:23 by jgambard          #+#    #+#             */
/*   Updated: 2020/05/22 15:42:40 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_cd(t_lst *args)
{
	if (!args->next)
	{
		ft_dprintf(2, "%s: %s\n", get_arg_value(args, 0), MISSING_ARGUMENT);
		status = ERROR_STATUS;
	}
	else if (chdir(get_arg_value(args, 1)) == -1)
	{
		ft_dprintf(2, "%s: %s: %s\n", get_arg_value(args, 0), strerror(errno),
					get_arg_value(args, 1));
		status = ERROR_STATUS;
	}
	else
		status = SUCCESS_STATUS;
}
