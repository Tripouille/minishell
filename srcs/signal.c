/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:52:41 by jgambard          #+#    #+#             */
/*   Updated: 2020/06/17 17:41:57 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

void	sigint_handler(int s)
{
	(void)s;
	g_status = 130;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	sigquit_handler(int signal)
{
	if (g_child_pid != -1)
	{
		g_status = 131;
		kill(g_child_pid, signal);
		ft_printf("Quit (Core Dumped)\n");
	}
}
