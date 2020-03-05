/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:58:16 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/05 01:46:40 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Display prompt matching prompt_name and write/append next command in buffer.
*/

void	ask_for_command(char *prompt_name, char *buffer)
{
	char				*prompt_value;
	int					read_ret;

	if ((prompt_value = get_variable_value(prompt_name, slen(prompt_name))))
		write(1, prompt_value, slen(prompt_value));
	if ((read_ret = read(0, buffer, BUFFER_SIZE)) == -1)
		error_exit("Read error");
	if (read_ret && buffer[read_ret - 1] == '\n')
		read_ret--;
	buffer[read_ret] = 0;
}

/*
** Search for the command in the list of builtins or write error message.
*/

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

/*
** Calloc and fill command array, run then free for each command in the buffer.
*/

void	parse_buffer(char *buffer, t_builtin builtins[])
{
	char	**command_args;

	while (*buffer)
	{
		if (!(command_args = ft_calloc(sizeof(char*), count_args(buffer) + 1)))
			error_exit("Malloc fail");
		fill_command_args(&buffer, command_args);
		run_command(command_args, builtins);
		free_command(command_args);
	}
}
