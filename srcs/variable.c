/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 04:21:42 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/06 07:39:09 by jgambard         ###   ########.fr       */
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

void		set_variable(char *variable)
{
	int		pos;
	int		name_len;
	char	*variable_name;

	name_len = variable_name_len(variable);
	if (!(variable_name = ft_strndup(variable, name_len)))
		error_exit("Malloc fail");
	pos = get_variable_pos(variable_name);
	free(variable_name);
	if (pos == -1)
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

	size = tab_size(env);
	new_env = 0;
	if (!variable || !(new_env = ft_calloc(sizeof(char*), size + 2)))
		error_exit("Malloc fail");
	new_env[size] = variable;
	while (size--)
		new_env[size] = env[size];
	free(env);
	env = new_env;
}

char		*get_variable_value(char *variable_name)
{
	int		pos;

	if ((pos = get_variable_pos(variable_name)) == -1)
		return ("");
	return (env[pos] + variable_name_len(env[pos]) + 1);
}
