/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 02:52:18 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/28 20:31:40 by aalleman         ###   ########lyon.fr   */
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
** Replace name of variable with its value after a $ in a command.
*/

void	replace_variable(char **buffer, char **arg)
{
	char	*variable_value;

	++*buffer;
	variable_value = get_variable_value(*buffer);
	while (*variable_value)
		*((*arg)++) = *variable_value++;
	*buffer += variable_name_len(*buffer) - 1;
}

/*
** Count length of command argument, excluding quotes.
** quote = what kind of quote is open, 0 if none
*/

int		arg_len(char *buffer)
{
	int		len;
	char	quote;
	int		name_len;

	len = 0;
	quote = 0;
	while (*buffer && (quote || cinstr(" ;|", *buffer) == -1))
	{
		if (*buffer == quote)
			quote = 0;
		else if (!quote && (*buffer == '\'' || *buffer == '"'))
			quote = *buffer;
		else if (quote != '\'' && *buffer == '$')
		{
			name_len = variable_name_len(buffer + 1);
			len += ft_strlen(get_variable_value(buffer + 1));
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

	len = ft_strlen(buffer);
	buffer[len++] = '\n';
	ask_for_command(quote == '\'' ? "PROMPT_QUOTE" : "PROMPT_DQUOTE",
						buffer + len);
	return (buffer);
}
