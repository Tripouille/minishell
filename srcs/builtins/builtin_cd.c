/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 04:31:23 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/10 01:44:28 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_cd(char **args)
{
	if (!args[1])
	{
		write(2, *args, slen(*args));
		write(2, ": ", 2);
		write(2, MISSING_ARGUMENT, slen(MISSING_ARGUMENT));
		write(2, "\n", 1);
		status = ERROR_STATUS;
	}
	else if (chdir(args[1]) == -1)
	{
		write(2, args[0], slen(args[0]));
		write(2, ": ", 2);
		write(2, strerror(errno), slen(strerror(errno)));
		write(2, ": ", 2);
		write(2, args[1], slen(args[1]));
		write(2, "\n", 1);
		status = ERROR_STATUS;
	}
	else
		status = SUCCESS_STATUS;
}
