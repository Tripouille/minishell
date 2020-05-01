/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:58:16 by jgambard          #+#    #+#             */
/*   Updated: 2020/05/01 19:18:44 by aalleman         ###   ########lyon.fr   */
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
	char				*prompt_color;
	int					read_ret;

	prompt_value = get_variable_value(prompt_name);
	prompt_color = get_variable_value("PROMPT_COLOR");
	write(1, prompt_color, ft_strlen(prompt_color));
	write(1, prompt_value, ft_strlen(prompt_value));
	write(1, RESET, ft_strlen(RESET));
	if ((read_ret = read(0, buffer, BUFFER_SIZE)) == -1)
		error_exit("Read error");
	if (read_ret && buffer[read_ret - 1] == '\n')
		read_ret--;
	buffer[read_ret] = 0;
}

/*
** Search for the command in the list of builtins or write error message.
*/

void	run_command(t_cmd_infos *cmd_infos, t_builtin builtins[])
{
	int		i_builtins;

	i_builtins = 0;
	while (builtins[i_builtins].name
	&& ft_strcmp(builtins[i_builtins].name, cmd_infos->args->content))
		i_builtins++;
	if (builtins[i_builtins].name)
		builtins[i_builtins].function(cmd_infos->args);
	else if (((char*)(cmd_infos->args->content))[0] == '.')
		launch_executable(cmd_infos->args);
	else if (!launch_executable_in_path(cmd_infos->args))
		minishell_error(COMMAND_NOT_FOUND, cmd_infos->args->content);
}

void	format_arg(char **buffer, char *arg, int arg_length)
{
	int		quote;
	int		i;

	quote = 0;
	i = 0;
	while (i < arg_length)
	{
		if (**buffer == quote)
			quote = 0;
		else if (!quote && (**buffer == '\'' || **buffer == '"'))
			quote = **buffer;
		else if (quote != '\'' && **buffer == '$')
			replace_variable(buffer, arg, &i);
		else
			arg[i++] = **buffer;
		(*buffer)++;
	}
	if (quote)
		(*buffer)++;
	arg[i] = 0;
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
		if (cinstr(";|\n", *buffer) != -1)
			buffer++;
		if (!(cmd_infos = ft_calloc(1, sizeof(cmd_infos))))
			error_exit("Malloc fail");
		if (!(command = ft_lst_addback(&commands, ft_lst_new(cmd_infos))))
			error_exit("Malloc fail");
		while (cinstr(";|", *buffer) == -1)
		{
			skip_spaces(&buffer, 0);
			arg_length = arg_len(buffer);
			printf("arg length = %d - parse buffer %c\n", arg_length, *buffer);
			if (!(arg = ft_calloc(arg_length, sizeof(char))))
				error_exit("Malloc fail");
			format_arg(&buffer, arg, arg_length);
			if (!ft_lst_addback(&(cmd_infos->args), ft_lst_new(arg)))
				error_exit("Malloc fail");
			skip_spaces(&buffer, 0);
		}
		cmd_infos->pipefd[0] = 0;
		cmd_infos->pipefd[1] = 1;
	}
}