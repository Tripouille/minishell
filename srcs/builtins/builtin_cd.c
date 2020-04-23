/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 04:31:23 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/23 18:37:55 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_cd(char **args)
{
	if (!args[1])
	{
		write(2, *args, ft_strlen(*args));
		write(2, ": ", 2);
		write(2, MISSING_ARGUMENT, ft_strlen(MISSING_ARGUMENT));
		write(2, "\n", 1);
		status = ERROR_STATUS;
	}
	else if (chdir(args[1]) == -1)
	{
		write(2, args[0], ft_strlen(args[0]));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, ": ", 2);
		write(2, args[1], ft_strlen(args[1]));
		write(2, "\n", 1);
		status = ERROR_STATUS;
	}
	else
		status = SUCCESS_STATUS;
}
