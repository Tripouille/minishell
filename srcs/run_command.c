/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:58:16 by jgambard          #+#    #+#             */
/*   Updated: 2020/06/24 18:04:17 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Search for the command in the list of builtins or write error message.
*/

void			run_command(t_cmd_infos *cmd_infos)
{
	t_function		builtin;
	char			*cmd_name;

	synchronize_fd(cmd_infos);
	cmd_name = get_cmd_name(cmd_infos);
	builtin = get_builtins_fct(cmd_name);
	if (builtin)
		builtin(cmd_infos->args);
	else if (cmd_name[0] == '.')
		launch_executable(cmd_infos->args);
	else if (!launch_executable_in_path(cmd_infos->args))
		minishell_error(COMMAND_NOT_FOUND, cmd_name, 127);
	restore_fd(cmd_infos);
}

char			*get_cmd_name(t_cmd_infos *cmd_infos)
{
	return (((t_argument*)cmd_infos->args->content)->s);
}

t_function		get_builtins_fct(char *cmd_name)
{
	int				i;

	i = 0;
	while (g_builtins[i].name && ft_strcmp(g_builtins[i].name, cmd_name))
		i++;
	return (g_builtins[i].function);
}
