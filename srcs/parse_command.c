/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:41:50 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/23 18:37:55 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Count number of arguments in command and ask to complete quotes.
*/

int		count_args(char *buffer)
{
	int		i;
	int		count;
	char	quote;

	count = 0;
	quote = 0;
	i = 0;
	while (buffer[i] && (quote || buffer[i] != ';'))
	{
		skip_spaces(buffer, &i);
		if (buffer[i] && buffer[i] != ';')
			count++;
		while (buffer[i] && (quote || cinstr(" ;", buffer[i]) == -1))
		{
			if (buffer[i] == quote)
				quote = 0;
			else if (!quote && (buffer[i] == '\'' || buffer[i] == '"'))
				quote = buffer[i];
			i++;
		}
	}
	if (quote)
		return (count_args(wait_for_rest(buffer, quote)));
	return (count);
}

/*
** Calloc an argument of the command.
*/

void	calloc_arg(char **command_args, int i_args, int size)
{
	if (!(command_args[i_args] = ft_calloc(sizeof(char), size)))
	{
		free_command(command_args);
		error_exit("Malloc fail");
	}
}

/*
** Fill the array of command arguments.
*/

void	fill_command_args(char **buffer, char **command_args)
{
	int		i_args;
	int		i_copy;
	char	quote;

	i_args = 0;
	quote = 0;
	while (**buffer && (quote || **buffer != ';'))
	{
		skip_spaces(buffer, 0);
		if (**buffer && **buffer != ';')
			calloc_arg(command_args, i_args, arg_len(*buffer) + 1);
		i_copy = 0;
		while (**buffer && (quote || cinstr(" ;", **buffer) == -1))
		{
			if (**buffer == quote)
				quote = 0;
			else if (!quote && (**buffer == '\'' || **buffer == '"'))
				quote = **buffer;
			else if (quote != '\'' && **buffer == '$')
				replace_variable(buffer, command_args[i_args], &i_copy);
			else
				command_args[i_args][i_copy++] = **buffer;
			++*buffer;
		}
		i_args++;
	}
}
