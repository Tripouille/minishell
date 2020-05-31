/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 04:21:42 by jgambard          #+#    #+#             */
/*   Updated: 2020/05/31 13:34:31 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		del_variable(char *variable_name)
{
	int		pos;

	if ((pos = get_variable_pos(variable_name)) == -1)
		return ;
	free(g_env[pos]);
	while (g_env[++pos])
		g_env[pos - 1] = g_env[pos];
	g_env[pos - 1] = g_env[pos];
}

/*
** Search for the variable in env if found replace it, in other case create it.
*/

void		set_variable(char *variable)
{
	int		pos;

	if ((pos = get_variable_pos(variable)) == -1)
		add_variable(ft_strdup(variable));
	else
	{
		free(g_env[pos]);
		if (!(g_env[pos] = ft_strdup(variable)))
			error_exit("Malloc fail");
	}
}

void		add_variable(char *variable)
{
	char		**new_env;
	int			size;

	size = str_array_size(g_env);
	new_env = 0;
	if (!variable || !(new_env = ft_calloc(sizeof(char*), size + 2)))
		error_exit("Malloc fail");
	new_env[size] = variable;
	while (size--)
		new_env[size] = g_env[size];
	free(g_env);
	g_env = new_env;
}
