/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 04:20:02 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/24 17:11:55 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_pwd(char **args)
{
	char		pwd[PATH_MAX];

	if (args[1])
	{
		usage_error(args[0], TOO_MANY_ARGUMENTS, "");
		status = ERROR_STATUS;
		return ;
	}
	getcwd(pwd, PATH_MAX);
	ft_printf("%s\n", pwd);
	status = SUCCESS_STATUS;
}
