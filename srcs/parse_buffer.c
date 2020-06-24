/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 19:13:16 by aalleman          #+#    #+#             */
/*   Updated: 2020/06/24 19:36:35 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parse_buffer(char *buffer)
{
	int				pipefd[2];
	t_lst			*command;
	t_cmd_infos		*cmd_infos;

	pipefd[IN] = STDIN_FILENO;
	while (*buffer)
	{
		if (handle_command(&buffer, &command, &cmd_infos) == -1)
		{
			minishell_error("parse error", "", 1);
			return (-1);
		}
		cmd_infos->fd[IN] = pipefd[IN];
		pipefd[IN] = STDIN_FILENO;
		pipefd[OUT] = STDOUT_FILENO;
		if (*buffer == '|')
			pipe(pipefd);
		cmd_infos->fd[OUT] = pipefd[OUT];
		if (*buffer && cinstr(";|", *buffer) != -1)
			++buffer;
	}
	return (0);
}

int		handle_command(char **buffer, t_lst **command, t_cmd_infos **cmd_infos)
{
	t_lst	*args;

	skip_spaces(buffer, 0);
	if (!**buffer)
		return (0);
	if (!(*cmd_infos = ft_calloc(1, sizeof(**cmd_infos))))
		error_exit("Malloc fail");
	if (!(*command = ft_lst_addback(&g_commands, ft_lst_new(*cmd_infos))))
		error_exit("Malloc fail");
	if (fill_args(buffer, &((*cmd_infos)->args)) == -1)
		return (-1);
	args = (*cmd_infos)->args;
	if (args && ft_strcmp(get_arg_value((*cmd_infos)->args, 0), "export") == 0)
		while ((args = args->next))
			if (get_arg_value(args, 0)[0] != '='
			&& is_identifier(get_arg_value(args, 0)))
				set_variable(get_arg_value(args, 0), 1);
	return (0);
}

int		fill_args(char **buffer, t_lst **args)
{
	int				arg_length;

	while (cinstr(";|", **buffer) == -1)
	{
		skip_spaces(buffer, 0);
		arg_length = arg_len(*buffer);
		if (arg_length == 0 && **buffer == '$')
		{
			*buffer += variable_name_len(*buffer + 1) + 1;
			skip_spaces(buffer, 0);
			if (cinstr(";|", **buffer) != -1)
				return (0);
		}
		else
			handle_argument(buffer, arg_length, args);
		skip_spaces(buffer, 0);
	}
	return (*args ? 0 : -1);
}
