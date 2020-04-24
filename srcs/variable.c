/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 04:21:42 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/24 12:28:01 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		del_variable(char *variable_name)
{
	int		pos;

	if ((pos = get_variable_pos(variable_name)) == -1)
		return ;
	free(env[pos]);
	while (env[++pos])
		env[pos - 1] = env[pos];
	env[pos - 1] = env[pos];
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
		free(env[pos]);
		if (!(env[pos] = ft_strdup(variable)))
			error_exit("Malloc fail");
	}
}

void		add_variable(char *variable)
{
	char		**new_env;
	int			size;

	size = str_array_size(env);
	new_env = 0;
	if (!variable || !(new_env = ft_calloc(sizeof(char*), size + 2)))
		error_exit("Malloc fail");
	new_env[size] = variable;
	while (size--)
		new_env[size] = env[size];
	free(env);
	env = new_env;
}
