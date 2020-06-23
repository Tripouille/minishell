/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 19:46:44 by aalleman          #+#    #+#             */
/*   Updated: 2020/06/23 20:32:26 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool		cmd_is_invalid(t_cmd_infos *cmd_infos)
{
	t_lst	*arg;
	char	*actual;
	char	*next;

	arg = cmd_infos->args;
	while (arg && arg->next)
	{
		actual = get_arg_value(arg, 0);
		next = get_arg_value(arg, 1);
		if (cinstr("><", actual[ft_strlen(actual) - 1]) != -1
		&& cinstr("><", next[0]) != -1)
		{
			minishell_error("parse error", "", 1);
			return (1);
		}
		arg = arg->next;
	}
	return (0);
}

t_bool		invalid_redirection(void)
{
	t_lst	*cmd;

	cmd = g_commands;
	while (cmd)
	{
		if (cmd_is_invalid(cmd->content))
			return (1);
		cmd = cmd->next;
	}
	return (0);
}
