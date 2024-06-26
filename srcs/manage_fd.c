/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 20:45:41 by aalleman          #+#    #+#             */
/*   Updated: 2020/06/17 16:51:47 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	synchronize_fd(t_cmd_infos *cmd_infos)
{
	dup2(cmd_infos->fd[IN], STDIN_FILENO);
	dup2(cmd_infos->fd[OUT], STDOUT_FILENO);
}

void	restore_fd(t_cmd_infos *cmd_infos)
{
	if (cmd_infos->fd[IN] != STDIN_FILENO)
	{
		close(cmd_infos->fd[IN]);
		dup2(g_fd_save[IN], STDIN_FILENO);
	}
	if (cmd_infos->fd[OUT] != STDOUT_FILENO)
	{
		close(cmd_infos->fd[OUT]);
		dup2(g_fd_save[OUT], STDOUT_FILENO);
	}
}
