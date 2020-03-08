/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 23:50:09 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/07 23:50:28 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			variable_name_len(char *variable_name)
{
	int		len;

	len = 0;
	while (variable_name[len] && variable_name[len] != '=')
		len++;
	return (len);
}

int			get_variable_pos(char *variable_name)
{
	int		i;
	int		arg_len;

	arg_len = slen(variable_name);
	i = -1;
	while (env[++i])
		if (arg_len == variable_name_len(env[i])
		&& !ft_strncmp(variable_name, env[i], arg_len))
			return (i);
	return (-1);
}

char		*get_variable_value(char *variable_name)
{
	int		pos;

	if ((pos = get_variable_pos(variable_name)) == -1)
		return ("");
	return (env[pos] + variable_name_len(env[pos]) + 1);
}
