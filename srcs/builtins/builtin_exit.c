/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 21:49:09 by jgambard          #+#    #+#             */
/*   Updated: 2020/05/31 13:40:31 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_exit(t_lst *args)
{
	(void)args;
	ft_lst_purge(&g_commands, purge_cmd);
	free_env();
	exit(EXIT_SUCCESS);
}
