/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 04:40:57 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/08 04:57:51 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		launch_executable(char **command_args)
{
	int		child_pid;
	int		ret;

	ret = 1;
	child_pid = fork();
	if (child_pid)
		ret = waitpid(child_pid, 0, 0);
	if (!child_pid && execve(command_args[0], command_args, env) == -1)
	{
		minishell_error(strerror(errno), command_args[0]);
		exit(EXIT_FAILURE);
	}
	return (ret);
}
