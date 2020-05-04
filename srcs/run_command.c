/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:58:16 by jgambard          #+#    #+#             */
/*   Updated: 2020/05/04 20:12:46 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Search for the command in the list of builtins or write error message.
*/

void	run_command(t_cmd_infos *cmd_infos, t_builtin builtins[], int fd_save[])
{
	t_function		builtin;

	synchronize_fd(cmd_infos);
	builtin = get_builtins_fct(builtins, cmd_infos->args->content);
	if (builtin)
		builtin(cmd_infos->args);
	else if (((char*)(cmd_infos->args->content))[0] == '.')
		launch_executable(cmd_infos->args);
	else if (!launch_executable_in_path(cmd_infos->args))
		minishell_error(COMMAND_NOT_FOUND, cmd_infos->args->content);
	restore_fd(cmd_infos, fd_save);
}

t_function		get_builtins_fct(t_builtin builtins[], char *cmd_name)
{
	int				i;

	i = 0;
	while (builtins[i].name	&& ft_strcmp(builtins[i].name, cmd_name))
		i++;
	return (builtins[i].function);
}
