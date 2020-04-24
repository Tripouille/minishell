/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 23:50:09 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/24 15:33:24 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_identifier(char *str)
{
	if (ft_isdigit(*str))
		return (0);
	while (ft_isalphanum(*str) || *str == '_')
		str++;
	if (*str == '=')
		return (1);
	return (0);
}

int			variable_name_len(char *variable_name)
{
	int		len;

	len = 0;
	while (variable_name[len] && variable_name[len] != '=')
		len++;
	return (len);
}

int			variable_comp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] && s1[i] != '=' && s1[i] == s2[i])
		i++;
	if ((!s1[i] && s2[i] == '=') || (s1[i] == '=' && !s2[i]))
		return (0);
	return (s1[i] - s2[i]);
}

int			get_variable_pos(char *variable_name)
{
	int		i;

	i = -1;
	while (env[++i])
		if (!variable_comp(variable_name, env[i]))
			return (i);
	return (-1);
}

/*
** Variable name is without $.
*/

char		*get_variable_value(char *variable_name)
{
	int				pos;
	static char		buffer[11];

	if (variable_name[0] == '?')
		return (ft_itoa_copy(buffer, status));
	else if ((pos = get_variable_pos(variable_name)) == -1)
		return ("");
	return (env[pos] + variable_name_len(env[pos]) + 1);
}
