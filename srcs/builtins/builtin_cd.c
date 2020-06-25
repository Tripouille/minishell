/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 04:31:23 by jgambard          #+#    #+#             */
/*   Updated: 2020/06/25 15:56:02 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		set_pwd_for_cd(t_lst *args)
{
	char		pwd[PATH_MAX];
	char		*join;
	char		new_variable[PATH_MAX];

	g_status = SUCCESS_STATUS;
	if (getcwd(pwd, PATH_MAX))
		join = ft_strjoin(2, "PWD=", pwd);
	else
	{
		usage_error("cd", "bad path", strerror(errno), SUCCESS_STATUS);
		join = ft_strjoin(4, "PWD=", get_variable_value("PWD"),
							"/", get_arg_value(args, 1));
	}
	ft_strlcpy(new_variable, join, ft_strlen(join) + 1);
	free(join);
	set_variable(new_variable, 0);
}

void		builtin_cd(t_lst *args)
{
	if (!args->next)
	{
		if (get_variable_pos("HOME") == -1)
			minishell_error("cd", "« HOME » undefined",
								ERROR_STATUS);
		else if (chdir(get_variable_value("HOME")) == -1)
			usage_error("cd", strerror(errno),
					get_variable_value("HOME"), ERROR_STATUS);
		else
		{
			g_status = SUCCESS_STATUS;
			set_variable(ft_strjoin(2, "PWD=", get_variable_value("HOME")), 0);
		}
	}
	else if (args->next && args->next->next)
		usage_error("cd", TOO_MANY_ARGUMENTS, "", ERROR_STATUS);
	else if (chdir(get_arg_value(args, 1)) == -1)
		usage_error("cd", strerror(errno), get_arg_value(args, 1),
						ERROR_STATUS);
	else
		set_pwd_for_cd(args);
}
