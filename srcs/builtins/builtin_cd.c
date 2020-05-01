/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 04:31:23 by jgambard          #+#    #+#             */
/*   Updated: 2020/05/01 18:59:54 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_cd(t_lst *args)
{
	if (!args->next)
	{
		ft_dprintf(2, "%s: %s\n", args->content, MISSING_ARGUMENT);
		status = ERROR_STATUS;
	}
	else if (chdir(get_argc(args, 1)) == -1)
	{
		ft_dprintf(2, "%s: %s: %s\n", get_argc(args, 0), strerror(errno),
					get_argc(args, 1));
		status = ERROR_STATUS;
	}
	else
		status = SUCCESS_STATUS;
}
