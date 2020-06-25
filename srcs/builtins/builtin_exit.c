/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 21:49:09 by jgambard          #+#    #+#             */
/*   Updated: 2020/06/25 15:27:17 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int						is_number(char *str)
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

void					ft_exit(long ret, int display)
{
	ft_lst_purge(&g_commands, purge_cmd);
	free_env();
	if (display)
		ft_dprintf(2, "exit\n");
	exit(ret);
}

unsigned long long		convert_number(const char *str, int *minus)
{
	unsigned long long		result;

	result = 0;
	*minus = 0;
	while (str && ((*str >= 9 && *str <= 13) || *str == ' '))
		str++;
	if (*str == '-' || *str == '+')
		*minus = (*str++ == '-' ? 1 : 0);
	while (*str >= '0' && *str <= '9')
		result = (result * 10) + (*str++ - '0');
	return (result);
}

void					builtin_exit(t_lst *args)
{
	unsigned long long		r;
	int						minus;

	if (args && args->next && args->next->next)
	{
		minishell_error("exit", TOO_MANY_ARGUMENTS, 1);
		return ;
	}
	if (args && args->next)
	{
		r = convert_number(get_arg_value(args, 1), &minus);
		if (r > __LONG_MAX__ || !is_number(get_arg_value(args, 1)))
		{
			minishell_error("exit", "argument must be numeric", 2);
			r = 2;
		}
		ft_exit(r * (minus ? -1 : 1), 1);
	}
	else
		ft_exit(g_status, 1);
}
