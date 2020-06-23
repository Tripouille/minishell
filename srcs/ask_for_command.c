/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ask_for_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 19:09:51 by aalleman          #+#    #+#             */
/*   Updated: 2020/06/23 19:26:18 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Display prompt matching prompt_name and write/append next command in buffer
** (can be an already filled buffer).
** Ends the command with a \0 and removes the \n if necessary.
*/

int		ask_for_command(char *prompt_name, char *buffer, int pos,
						int first_call)
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
			return (dup2(g_fd_save[IN], STDIN_FILENO) - 1);
		if (!read_ret && !ft_strlen(buffer) && first_call)
			ft_exit(0, 1);
		else if (!read_ret && !first_call && ft_printf("\n"))
			return (ask_for_command("PROMPT", buffer, 0, 1));
		if (buffer[pos + read_ret - 1] == '\n' && read_ret-- > -1)
			continue_reading = 0;
		else
			pos = ft_strlen(buffer);
	}
	buffer[pos + read_ret] = 0;
	return (check_buffer(buffer));
}

/*
** If there's an odd number of quotes, ask for the missing one.
*/

int		check_buffer(char *buffer)
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
		return (ask_for_command("PROMPT", buffer, 0, 1));
	}
	if (quote)
		return (ask_for_command(quote == '\'' ?
				"PROMPT_QUOTE" : "PROMPT_DQUOTE", buffer, i, 0));
	else if (((i > 1 && buffer[i - 2] != '\\') || i == 1) && last_char == '|')
		return (ask_for_command("PROMPT_PIPE", buffer, i, 0));
	return (0);
}

int		check_buffer2(char *buffer, int *i, char *quote, char *last_char)
{
	char	escaped;

	escaped = 0;
	while (buffer[*i])
	{
		while (!ft_strncmp(buffer + *i, "\\\\", 2))
			*i += 2;
		escaped = buffer[*i] == '\\' && *quote != '\'' ? 1 : 0;
		if (escaped && ++*i)
			*last_char = '\\';
		if (!escaped && buffer[*i] == *quote)
			*quote = 0;
		else if (!escaped && !*quote
					&& (buffer[*i] == '\'' || buffer[*i] == '"'))
			*quote = buffer[*i];
		if (((buffer[*i] == '|' && (*last_char == '|' || *last_char == ';'))
		|| !ft_strncmp(buffer + *i, ">>>", 3)
		|| !ft_strncmp(buffer + *i, "<<", 2)) && !*quote)
			return (-1);
		if (!ft_isspace(buffer[*i]))
			*last_char = buffer[*i];
		if (buffer[*i])
			++*i;
	}
	return (0);
}
