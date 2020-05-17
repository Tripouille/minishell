/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 19:13:16 by aalleman          #+#    #+#             */
/*   Updated: 2020/05/17 03:00:41 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parse_buffer(char *buffer)
{
	t_lst			*command;
	t_cmd_infos		*cmd_infos;
	int				pipefd[2];
	
	pipefd[IN] = STDIN_FILENO;
	while (*buffer)
	{
		skip_spaces(&buffer, 0);
		if (cinstr(";|", *buffer) != -1)
			buffer++;
		if (cinstr(";|", *buffer) != -1 && *buffer)
		{
			minishell_error("parse error", "");
			return (-1);
		}
		skip_spaces(&buffer, 0);
		if (!*buffer)
			return (0);
		if (!(cmd_infos = ft_calloc(1, sizeof(cmd_infos))))
			error_exit("Malloc fail");
		if (!(command = ft_lst_addback(&commands, ft_lst_new(cmd_infos))))
			error_exit("Malloc fail");
		fill_args(&buffer, &(cmd_infos->args));
		cmd_infos->fd[IN] = pipefd[IN];
		pipefd[IN] = STDIN_FILENO;
		pipefd[OUT] = STDOUT_FILENO;
		if (*buffer == '|')
			pipe(pipefd);
		cmd_infos->fd[OUT] = pipefd[OUT];
	}
	return (0);
}

void	fill_args(char **buffer, t_lst **args)
{
	char			*arg;
	int				arg_length;
	
	while (cinstr(";|", **buffer) == -1)
	{
		skip_spaces(buffer, 0);
		arg_length = arg_len(*buffer);
		if (!(arg = ft_calloc(arg_length, sizeof(char))))
			error_exit("Malloc fail");
		format_arg(buffer, arg, arg_length);
		if (!ft_lst_addback(args, ft_lst_new(arg)))
			error_exit("Malloc fail");
		skip_spaces(buffer, 0);
	}
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
