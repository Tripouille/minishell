/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ask_for_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 19:09:51 by aalleman          #+#    #+#             */
/*   Updated: 2020/05/31 14:05:01 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Display prompt matching prompt_name and write/append next command in buffer
** (can be an already filled buffer).
** Ends the command with a \0 and removes the \n if necessary.
*/

void	ask_for_command(char *prompt_name, char *buffer, int pos)
{
	int					read_ret;

	ft_printf("%s%s%s", get_variable_value("PROMPT_COLOR"),
				get_variable_value(prompt_name), RESET);
	if ((read_ret = read(0, buffer + pos, BUFFER_SIZE - pos - 1)) == -1)
		error_exit("Read error");
	if (read_ret && buffer[pos + read_ret - 1] == '\n')
		read_ret--;
	buffer[pos + read_ret] = 0;
	check_buffer(buffer);
}

/*
** If there's an odd number of quotes, ask for the missing one.
*/

void	check_buffer(char *buffer)
{
	int		i;
	int		quote;
	char	last_char;

	quote = 0;
	i = -1;
	while (buffer[++i])
	{
		if (buffer[i] == quote)
			quote = 0;
		else if (!quote && (buffer[i] == '\'' || buffer[i] == '"'))
			quote = buffer[i];
		if (buffer[i] == '|' && last_char == '|' && !quote)
		{
			minishell_error("parse error", "");
			return (ask_for_command("PROMPT", buffer, 0));
		}
		if (!ft_isspace(buffer[i]) && buffer[i] != ';')
			last_char = buffer[i];
	}
	if (quote)
		ask_for_command(quote == '\'' ? "PROMPT_QUOTE" : "PROMPT_DQUOTE",
						buffer, i);
	else if (last_char == '|')
		ask_for_command("PROMPT_PIPE", buffer, i);
}
