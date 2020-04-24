/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 04:31:23 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/24 12:37:26 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_cd(char **args)
{
	if (!args[1])
	{
		ft_dprintf(2, "%s: %s\n", args[0], MISSING_ARGUMENT);
		status = ERROR_STATUS;
	}
	else if (chdir(args[1]) == -1)
	{
		ft_dprintf(2, "%s: %s: %s\n", args[0], strerror(errno), args[1]);
		status = ERROR_STATUS;
	}
	else
		status = SUCCESS_STATUS;
}
