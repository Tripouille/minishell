/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 00:33:40 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/06 04:16:06 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			tab_size(char **tab)
{
	int		size;

	size = 0;
	while (tab[size])
		size++;
	return (size);
}

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

void		free_env(void)
{
	int		i;

	if (!env)
		return ;
	i = -1;
	while (env[++i])
		free(env[i]);
	free(env);
}

void		copy_environment(void)
{
	int		size;
	int		i;

	size = tab_size(environ);
	if (!(env = ft_calloc(sizeof(char*), size + 1)))
		error_exit("Malloc fail");
	i = -1;
	while (++i < size)
		if (!(env[i] = ft_strdup(environ[i])))
			error_exit("Malloc fail");
}
