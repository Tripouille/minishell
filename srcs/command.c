/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:58:16 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/02 23:56:59 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_command(char **command_args, t_builtin builtins[])
{
	int		i_builtins;

	i_builtins = 0;
	while (builtins[i_builtins].name
	&& ft_strcmp(builtins[i_builtins].name, command_args[0]))
		i_builtins++;
	if (builtins[i_builtins].name)
		builtins[i_builtins].function(command_args);
	else
	{
		write(2, "Minishell: ", slen("Minishell: "));
		write(2, COMMAND_NOT_FOUND, slen(COMMAND_NOT_FOUND));
		write(2, command_args[0], slen(command_args[0]));
		write(2, "\n", 1);
	}
}

void	parse_buffer(char *buffer, t_builtin builtins[])
{
	char	**command_args;

	while (*buffer && *buffer != '\n')
	{
		parse_command(&buffer, &command_args);
		run_command(command_args, builtins);
		free_command(command_args);
	}
}
