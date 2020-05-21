/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 02:52:18 by jgambard          #+#    #+#             */
/*   Updated: 2020/05/21 12:27:11 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_argc(t_lst *args, int pos)
{
	while (pos-- && args)
		args = args->next;
	return (args ? args->content : 0);
}

void	destroy_arg(void *arg)
{
	free(((t_argument*)arg)->s);
	free(arg);
}

void	purge_cmd(void *cmd_infos)
{
	ft_lst_purge(&(((t_cmd_infos*)cmd_infos)->args), destroy_arg);
	free(cmd_infos);
}

/*
** Replace name of variable with its value after a $ in a command.
*/

void	replace_variable(char **buffer, char *arg, int *i)
{
	char	*variable_value;

	++*buffer;
	variable_value = get_variable_value(*buffer);
	while (*variable_value)
		arg[(*i)++] = *variable_value++;
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
		//printf("arg len %c\n", *buffer);
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
