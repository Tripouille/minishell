/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:41:50 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/01 21:52:43 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command(char **command_args)
{
	int		i_args;

	i_args = 0;
	while (command_args[i_args])
		free(command_args[i_args++]);
	free(command_args);
}

int		command_len(char *buffer)
{
	int		len;

	len = 0;
	while (buffer[len] && buffer[len] != ' ' && buffer[len] != '\n')
		len++;
	return (len);
}

void	fill_command_args(char **buffer, char **command_args)
{
	int		i_args;
	int		i_copy;

	i_args = 0;
	while (**buffer && **buffer != '\n')
	{
		while (**buffer == ' ')
			++*buffer;
		if (**buffer && !(command_args[i_args] =
		ft_calloc(sizeof(char), command_len(*buffer) + 1)))
		{
			free_command(command_args);
			error_exit("Malloc fail");
		}
		i_copy = 0;
		while (**buffer && **buffer != ' ' && **buffer != '\n')
		{
			command_args[i_args][i_copy++] = **buffer;
			++*buffer;
		}
		i_args++;
	}
}

int		count_args(char *buffer)
{
	int		count;

	count = 0;
	while (*buffer)
	{
		while (*buffer == ' ')
			buffer++;
		if (*buffer)
			count++;
		while (*buffer && *buffer != ' ')
			buffer++;
	}
	return (count);
}

void	parse_command(char **buffer, char ***command_args)
{
	if (!(*command_args = ft_calloc(sizeof(char*), count_args(*buffer) + 1)))
		error_exit("Malloc fail");
	fill_command_args(buffer, *command_args);
}
