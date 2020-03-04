/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 04:20:02 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/04 04:29:46 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_pwd(char **args)
{
	char		*pwd;

	if (args[1])
	{
		write(2, *args, slen(*args));
		write(2, ": ", 2);
		write(2, TOO_MANY_ARGUMENTS, slen(TOO_MANY_ARGUMENTS));
		write(2, "\n", 1);
		return ;
	}
	pwd = getwd(0);
	write(1, pwd, slen(pwd));
	write(1, "\n", 1);
	free(pwd);
}
