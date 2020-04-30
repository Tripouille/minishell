/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 21:49:09 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/30 18:23:10 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_exit(char **args)
{
	(void)args;
	ft_lst_purge(&commands, purge_cmd);
	free_env();
	exit(EXIT_SUCCESS);
}
