/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 00:33:40 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/06 03:05:25 by jgambard         ###   ########.fr       */
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
}

void		copy_environment(void)
{
	int		env_count;
	int		i;

	env_count = 0;
	while (environ[env_count])
		env_count++;
	if (!(env = ft_calloc(sizeof(char*), env_count + 1)))
		error_exit("Malloc fail");
	i = -1;
	while (++i < env_count)
		if (!(env[i] = ft_strdup(environ[i])))
			error_exit("Malloc fail");
}
