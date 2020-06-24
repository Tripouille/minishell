/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_argument.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 19:36:13 by aalleman          #+#    #+#             */
/*   Updated: 2020/06/24 19:38:20 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_argument(char **buffer, int arg_length, t_lst **args)
{
	t_argument		*arg;

	calloc_arg(&arg, arg_length);
	if (**buffer == '\'' || **buffer == '"' || !ft_strncmp("\\>",
	*buffer, 2) || !ft_strncmp("\\<", *buffer, 2))
		arg->quoted = TRUE;
	format_arg(buffer, arg->s);
	if (!ft_lst_addback(args, ft_lst_new(arg)))
		error_exit("Malloc fail");
}

void	calloc_arg(t_argument **arg, int arg_length)
{
	if (!(*arg = ft_calloc(1, sizeof(**arg))))
		error_exit("Malloc fail");
	if (!((*arg)->s = ft_calloc(arg_length + 1, sizeof(char))))
		error_exit("Malloc fail");
}

void	format_arg(char **buffer, char *arg)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (**buffer && (quote || cinstr(";| ", **buffer) == -1))
	{
		if (quote != '\'' && **buffer == '\\')
			handle_backslash(buffer, arg, &i, quote);
		else if (**buffer == quote)
			quote = 0;
		else if (!quote && (**buffer == '\'' || **buffer == '"'))
			quote = **buffer;
		else if (!quote && **buffer == '$' && (*buffer)[1] == '\"')
			;
		else if (quote != '\'' && **buffer == '$')
			replace_variable(buffer, arg, &i);
		else
			arg[i++] = **buffer;
		(*buffer)++;
	}
	if (quote)
		(*buffer)++;
	arg[i] = 0;
}
