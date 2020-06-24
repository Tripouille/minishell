/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 19:13:16 by aalleman          #+#    #+#             */
/*   Updated: 2020/06/24 12:50:24 by aalleman         ###   ########lyon.fr   */
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
			return (-1);
		if (!cmd_infos->args)
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
	skip_spaces(buffer, 0);
	if (!**buffer)
		return (0);
	if (!(*cmd_infos = ft_calloc(1, sizeof(**cmd_infos))))
		error_exit("Malloc fail");
	if (!(*command = ft_lst_addback(&g_commands, ft_lst_new(*cmd_infos))))
		error_exit("Malloc fail");
	fill_args(buffer, &((*cmd_infos)->args));
	return (0);
}

void	fill_args(char **buffer, t_lst **args)
{
	t_argument		*arg;
	int				arg_length;

	while (cinstr(";|", **buffer) == -1)
	{
		skip_spaces(buffer, 0);
		arg_length = arg_len(*buffer);
		if (arg_length == 0 && **buffer == '$')
			*buffer += variable_name_len(*buffer + 1) + 1;
		else
		{
			calloc_arg(&arg, arg_length);
			if (**buffer == '\'' || **buffer == '"'
			|| !ft_strncmp("\\>", *buffer, 2)
			|| !ft_strncmp("\\<", *buffer, 2))
				arg->quoted = TRUE;
			format_arg(buffer, arg->s);
			if (!ft_lst_addback(args, ft_lst_new(arg)))
				error_exit("Malloc fail");
		}
		skip_spaces(buffer, 0);
	}
}

void	calloc_arg(t_argument **arg, int arg_length)
{
	if (!(*arg = ft_calloc(1, sizeof(**arg))))
		error_exit("Malloc fail");
	if (!((*arg)->s = ft_calloc(arg_length + 1, sizeof(char))))
		error_exit("Malloc fail");
}

void	format_arg(char **buffer, char *arg)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (**buffer && (quote || cinstr(";| ", **buffer) == -1))
	{
		if (quote != '\'' && **buffer == '\\')
			handle_backslash(buffer, arg, &i, quote);
		else if (**buffer == quote)
			quote = 0;
		else if (!quote && (**buffer == '\'' || **buffer == '"'))
			quote = **buffer;
		else if (!quote && **buffer == '$' && (*buffer)[1] == '\"')
			;
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
