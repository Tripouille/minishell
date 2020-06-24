/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 23:50:09 by jgambard          #+#    #+#             */
/*   Updated: 2020/06/24 17:51:05 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_identifier(char *str)
{
	if (!*str)
		return (0);
	if (ft_isdigit(*str))
		return (0);
	while (ft_isalphanum(*str) || *str == '_')
		str++;
	if (*str == '=' || !*str)
		return (1);
	return (0);
}

int			variable_name_len(char *variable_name)
{
	int		len;

	if (*variable_name == '?' || ft_isdigit(*variable_name))
		return (1);
	len = 0;
	while (ft_isalphanum(variable_name[len]) || variable_name[len] == '_')
		len++;
	return (len);
}

int			variable_comp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while ((ft_isalphanum(s1[i]) || s1[i] == '_') && s1[i] == s2[i])
		i++;
	if (!(ft_isalphanum(s1[i]) || s1[i] == '_')
	&& !(ft_isalphanum(s2[i]) || s2[i] == '_'))
		return (0);
	return (s1[i] - s2[i]);
}

int			get_variable_pos(char *variable_name)
{
	int		i;

	i = -1;
	while (g_env[++i])
		if (!variable_comp(variable_name, g_env[i]))
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

	if (cinstr(" ;|$\"=", *variable_name) != -1)
		return ("$");
	else if (variable_name[0] == '?')
		return (ft_itoa_copy(buffer, g_status));
	else if ((pos = get_variable_pos(variable_name)) == -1)
		return ("");
	return (g_env[pos] + variable_name_len(g_env[pos]) + 1);
}
