/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 04:20:02 by jgambard          #+#    #+#             */
/*   Updated: 2020/06/24 16:00:47 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_pwd(t_lst *args)
{
	char		pwd[PATH_MAX];

	(void)args;
	g_status = SUCCESS_STATUS;
	if (!getcwd(pwd, PATH_MAX))
		ft_printf("%s\n", get_variable_value("PWD"));
	else
		ft_printf("%s\n", pwd);
}
