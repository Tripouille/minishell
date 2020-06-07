/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ask_for_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 19:09:51 by aalleman          #+#    #+#             */
/*   Updated: 2020/06/07 16:10:02 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Display prompt matching prompt_name and write/append next command in buffer
** (can be an already filled buffer).
** Ends the command with a \0 and removes the \n if necessary.
*/

int		ask_for_command(char *prompt_name, char *buffer, int pos)
{
	int					read_ret;
	int					continue_reading;

	ft_printf("%s%s%s", "\033[0;31m",
				get_variable_value(prompt_name), RESET);
	continue_reading = 1;
	ft_bzero(buffer + pos, BUFFER_SIZE - pos);
	while (continue_reading)
	{
		if ((read_ret = read(0, buffer + pos, BUFFER_SIZE - pos - 1)) == -1)
			error_exit("Read error");
		if (!read_ret && !ft_strlen(buffer + pos))
			return (EOF);
		if (buffer[pos + read_ret - 1] == '\n')
		{
			read_ret--;
			continue_reading = 0;
		}
		else
			pos = ft_strlen(buffer);
	}
	buffer[pos + read_ret] = 0;
	check_buffer(buffer);
	return (0);
}

/*
** If there's an odd number of quotes, ask for the missing one.
*/

void	check_buffer(char *buffer)
{
	int		i;
	char	quote;
	char	last_char;

	quote = 0;
	last_char = 0;
	i = 0;
	if (check_buffer2(buffer, &i, &quote, &last_char) == -1)
	{
		minishell_error("parse error", "", 2);
		return ((void)ask_for_command("PROMPT", buffer, 0));
	}
	if (quote)
		ask_for_command(quote == '\'' ? "PROMPT_QUOTE" : "PROMPT_DQUOTE",
						buffer, i);
	else if (((i > 1 && buffer[i - 2] != '\\') || i == 1) && last_char == '|')
		ask_for_command("PROMPT_PIPE", buffer, i);
}

int		check_buffer2(char *buffer, int *i, char *quote, char *last_char)
{
	char	escaped;

	escaped = 0;
	while (buffer[*i])
	{
		escaped = !escaped && buffer[*i] == '\\' && *quote != '\'' ? 1 : 0;
		if (escaped)
		{
			*last_char = '\\';
			++*i;
		}
		if (!escaped && buffer[*i] == *quote)
			*quote = 0;
		else if (!escaped && !*quote
					&& (buffer[*i] == '\'' || buffer[*i] == '"'))
			*quote = buffer[*i];
		if (buffer[*i] == '|' && (*last_char == '|' || *last_char == ';')
			&& !*quote)
			return (-1);
		if (!ft_isspace(buffer[*i]))
			*last_char = buffer[*i];
		if (buffer[*i])
			++*i;
	}
	return (0);
}
