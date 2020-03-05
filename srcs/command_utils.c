/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 02:52:18 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/05 01:42:41 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Free the array of command arguments.
*/

void	free_command(char **command_args)
{
	int		i_args;

	i_args = 0;
	while (command_args[i_args])
		free(command_args[i_args++]);
	free(command_args);
}

/*
** Count length of command argument, excluding quotes.
*/

int		arg_len(char *buffer)
{
	int		len;
	char	quote;
	int		name_len;

	len = 0;
	quote = 0;
	while (*buffer && (quote || *buffer != ' '))
	{
		if (*buffer == quote)
			quote = 0;
		else if (!quote && (*buffer == '\'' || *buffer == '"'))
			quote = *buffer;
		else if (quote != '\'' && *buffer == '$')
		{
			name_len = variable_name_len(buffer + 1);
			len += slen(get_variable_value(buffer + 1, name_len));
			buffer += name_len;
		}
		else
			len++;
		buffer++;
	}
	return (len);
}

/*
** If there's an odd number of quotes, ask for the missing one.
*/

char	*wait_for_rest(char *buffer, char quote)
{
	int		len;

	len = slen(buffer);
	buffer[len++] = '\n';
	ask_for_command(quote == '\'' ? "PROMPT_QUOTE" : "PROMPT_DQUOTE",
						buffer + len);
	return (buffer);
}
