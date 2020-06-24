/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 21:49:09 by jgambard          #+#    #+#             */
/*   Updated: 2020/06/24 13:27:23 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_number(char *str)
{
	if (!*str)
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (0);
	while (ft_isdigit(*str))
		str++;
	return (*str ? 0 : 1);
}

void		ft_exit(int ret, int display)
{
	ft_lst_purge(&g_commands, purge_cmd);
	free_env();
	if (display)
		ft_dprintf(2, "exit\n");
	exit(ret);
}

void		builtin_exit(t_lst *args)
{
	int		r;

	if (args && args->next)
	{
		if (!is_number(get_arg_value(args, 1)))
		{
			minishell_error("exit", "argument must be numeric", 2);
			r = 2;
		}
		else
			r = ft_atoi(get_arg_value(args, 1));
	}
	else
		r = EXIT_SUCCESS;
	ft_exit(r, 1);
}
