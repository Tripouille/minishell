/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:52:41 by jgambard          #+#    #+#             */
/*   Updated: 2020/06/14 20:24:31 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

void	sigint_handler(int s)
{
	(void)s;
	if (g_minishell_pid)
	{
		g_status = 130;
		write(1, "\n", 1);
		signal(SIGINT, SIG_IGN);
	}
	else
	{
		ft_lst_purge(&g_commands, purge_cmd);
		free_env();
		signal(SIGINT, SIG_DFL);
		kill(0, SIGINT);
	}
}

void	sigquit_handler(int signal)
{
	if (g_child_pid != -1)
	{
		g_status = 131;
		kill(g_child_pid, signal);
		ft_printf("Quit (Core Dumped)\n");
	}
	else if (g_minishell_pid)
		kill(g_minishell_pid, SIGINT);
}
