/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:58:16 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/28 20:34:07 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Display prompt matching prompt_name and write/append next command in buffer
** (can be an already filled buffer).
** Ends the command with a \0 and removes the \n if necessary.
*/

void	ask_for_command(char *prompt_name, char *buffer)
{
	char				*prompt_value;
	int					read_ret;

	if ((prompt_value = get_variable_value(prompt_name)))
		write(1, prompt_value, ft_strlen(prompt_value));
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
	else if (command_args[0][0] == '.')
		launch_executable(command_args);
	else if (!launch_executable_in_path(command_args))
		minishell_error(COMMAND_NOT_FOUND, command_args[0]);
}

void	format_arg(char *buffer, char *arg, int arg_length)
{
	int		quote;

	quote = 0;
	while (arg_length)
	{
		if (*buffer == quote)
			quote = 0;
		else if (!quote && (*buffer == '\'' || *buffer == '"'))
			quote = *buffer;
		else if (quote != '\'' && *buffer == '$')
			replace_variable(&buffer, &arg);
		else
			*arg++ = *buffer;
		buffer++;
	}
}

/*
** 
*/

void	parse_buffer(char *buffer)
{
	t_lst			*command;
	t_cmd_infos		*cmd_infos;
	char			*arg;
	int				arg_length;
	
	while (*buffer)
	{
		if (!(cmd_infos = malloc(sizeof(cmd_infos))))
			error_exit("Malloc fail");
		if (!(command = ft_lst_addback(&commands, ft_lst_new(cmd_infos))))
			error_exit("Malloc fail");
		while (cinstr(";|", *buffer) == -1)
		{
			arg_length = arg_len(buffer);
			if (!(arg = malloc(sizeof(char) * arg_length)))
				error_exit("Malloc fail");
			if (!ft_lst_addback(&(cmd_infos->args), ft_lst_new(arg)))
				error_exit("Malloc fail");
			format_arg(buffer, arg, arg_length);
			buffer += arg_length;
		}
	}
}