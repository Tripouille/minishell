/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:41:50 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/03 23:26:24 by jgambard         ###   ########.fr       */
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

int		command_len(char *buffer, char delimitor)
{
	int		len;

	len = 0;
	while (buffer[len] && buffer[len] != delimitor
	&& (delimitor != ' ' || (buffer[len] != '\'' && buffer[len] != '"')))
		len++;
	return (len);
}

void	fill_command_args(char **buffer, char **command_args)
{
	int		i_args;
	int		i_copy;
	char	delimitor;

	i_args = 0;
	delimitor = ' ';
	while (**buffer)
	{
		skip_spaces(buffer, 0);
		if (**buffer == '\'' || **buffer == '"')
			delimitor = *(*buffer)++;
		if (**buffer && !(command_args[i_args] =
		ft_calloc(sizeof(char), command_len(*buffer, delimitor) + 1)))
		{
			free_command(command_args);
			error_exit("Malloc fail");
		}
		i_copy = 0;
		while (**buffer
		&& **buffer != delimitor
		&& (delimitor != ' ' || (**buffer != '\'' && **buffer != '"')))
			command_args[i_args][i_copy++] = *(*buffer)++;
		if (**buffer == delimitor)
		{
			delimitor = ' ';
			++*buffer;
		}
		i_args++;
	}
}

char	*wait_for_rest(char *buffer, char delimitor)
{
	ask_for_command(delimitor == '\'' ? "PROMPT_QUOTE" : "PROMPT_DQUOTE",
						buffer + slen(buffer));
	return (buffer);
}

int		count_args(char *buffer)
{
	int		i;
	int		count;
	char	delimitor;

	count = 0;
	delimitor = ' ';
	i = 0;
	while (buffer[i])
	{
		skip_spaces(buffer, &i);
		if (buffer[i] == '\'' || buffer[i] == '"')
			delimitor = buffer[i++];
		if (buffer[i])
			count++;
		while (buffer[i]
		&& buffer[i] != delimitor
		&& (delimitor != ' ' || (buffer[i] != '\'' && buffer[i] != '"')))
			i++;
		if (buffer[i] == delimitor)
		{
			delimitor = ' ';
			i++;
		}
	}
	if (delimitor != ' ')
		return (count_args(wait_for_rest(buffer, delimitor)));
	return (count);
}

void	parse_command(char **buffer, char ***command_args)
{
	if (!(*command_args = ft_calloc(sizeof(char*), count_args(*buffer) + 1)))
		error_exit("Malloc fail");
	fill_command_args(buffer, *command_args);
}
