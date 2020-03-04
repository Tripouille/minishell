/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:41:50 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/04 03:07:42 by jgambard         ###   ########.fr       */
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
	while (buffer[i])
	{
		skip_spaces(buffer, &i);
		if (buffer[i])
			count++;
		while (buffer[i] && (quote || buffer[i] != ' '))
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
	while (**buffer)
	{
		skip_spaces(buffer, 0);
		if (**buffer)
			calloc_arg(command_args, i_args, arg_len(*buffer) + 1);
		i_copy = 0;
		while (**buffer && (quote || **buffer != ' '))
		{
			if (**buffer == quote)
				quote = 0;
			else if (!quote && (**buffer == '\'' || **buffer == '"'))
				quote = **buffer;
			else
				command_args[i_args][i_copy++] = **buffer;
			++*buffer;
		}
		i_args++;
	}
}
