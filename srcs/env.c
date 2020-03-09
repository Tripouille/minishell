/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 00:33:40 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/09 05:05:25 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_env(void)
{
	int		i;

	if (!env)
		return ;
	i = -1;
	while (env[++i])
		free(env[i]);
	free(env);
	env = 0;
}

void		copy_environment(void)
{
	int		size;
	int		i;

	size = str_array_size(environ);
	if (!(env = ft_calloc(sizeof(char*), size + 1)))
		error_exit("Malloc fail");
	i = -1;
	while (++i < size)
		if (!(env[i] = ft_strdup(environ[i])))
			error_exit("Malloc fail");
}