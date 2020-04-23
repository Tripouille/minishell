/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 04:20:02 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/23 18:37:55 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_pwd(char **args)
{
	char		*pwd;

	if (args[1])
	{
		write(2, *args, ft_strlen(*args));
		write(2, ": ", 2);
		write(2, TOO_MANY_ARGUMENTS, ft_strlen(TOO_MANY_ARGUMENTS));
		write(2, "\n", 1);
		status = ERROR_STATUS;
		return ;
	}
	pwd = getwd(0);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
	status = SUCCESS_STATUS;
}
