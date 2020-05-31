/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 00:33:40 by jgambard          #+#    #+#             */
/*   Updated: 2020/05/31 13:44:34 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_env(void)
{
	int		i;

	if (!g_env)
		return ;
	i = -1;
	while (g_env[++i])
		free(g_env[i]);
	free(g_env);
	g_env = 0;
}

void		copy_environment(char **envp)
{
	int		size;
	int		i;

	size = str_array_size(envp);
	if (!(g_env = ft_calloc(sizeof(char*), size + 1)))
		error_exit("Malloc fail");
	i = -1;
	while (++i < size)
		if (!(g_env[i] = ft_strdup(envp[i])))
			error_exit("Malloc fail");
}
