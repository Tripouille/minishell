/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 04:20:02 by jgambard          #+#    #+#             */
/*   Updated: 2020/05/31 13:40:46 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_pwd(t_lst *args)
{
	char		pwd[PATH_MAX];

	if (args->next)
	{
		usage_error(get_arg_value(args, 0), TOO_MANY_ARGUMENTS, "");
		g_status = ERROR_STATUS;
		return ;
	}
	getcwd(pwd, PATH_MAX);
	ft_printf("%s\n", pwd);
	g_status = SUCCESS_STATUS;
}
