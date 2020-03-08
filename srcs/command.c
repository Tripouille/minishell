/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:58:16 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/08 04:37:24 by jgambard         ###   ########.fr       */
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

	if ((prompt_value = get_variable_value(prompt_name)))
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
	int		child_pid;

	i_builtins = 0;
	while (builtins[i_builtins].name
	&& ft_strcmp(builtins[i_builtins].name, command_args[0]))
		i_builtins++;
	if (builtins[i_builtins].name)
		builtins[i_builtins].function(command_args);
	else if (command_args[0][0] == '.')
	{
		child_pid = fork();
		if (child_pid)
			waitpid(child_pid, 0, 0);
		if (!child_pid && execve(command_args[0], command_args + 1, env) == -1)
		{
			minishell_error(strerror(errno), command_args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
		minishell_error(COMMAND_NOT_FOUND, command_args[0]);
}

/*
** Calloc and fill command array, run then free for each command in the buffer.
*/

void	parse_buffer(char *buffer, t_builtin builtins[])
{
	char	**command_args;
	int		arg_nb;

	if (!(arg_nb = count_args(buffer)))
		return ;
	while (*buffer)
	{
		if (!(command_args = ft_calloc(sizeof(char*), arg_nb + 1)))
			error_exit("Malloc fail");
		fill_command_args(&buffer, command_args);
		run_command(command_args, builtins);
		free_command(command_args);
	}
}
