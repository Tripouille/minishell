/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 04:40:57 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/09 04:46:23 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_valid_path(char *command)
{
	char	**split;

	if (!(split = ft_split(get_variable_value("PATH"), ':')))
		error_exit("Malloc fail");
	while (*split)
	{
		(void)command;
		split++;
	}
	return (0);
}

int		launch_executable_in_path(char **command_args)
{
	//int		child_pid;
	//int		status;
//
	//child_pid = fork();
	//if (child_pid)
		//waitpid(child_pid, &status, 0);
	//if (!child_pid && execve(command_args[0], command_args, env) == -1)
	//{
		//minishell_error(strerror(errno), command_args[0]);
		//exit(EX_USAGE);
	//}
	//return (WEXITSTATUS(status) == EX_USAGE ? 0 : 1);
	get_valid_path(command_args[0]);
	return (0);
}

int		launch_executable(char **command_args)
{
	int		child_pid;
	int		status;

	child_pid = fork();
	if (child_pid)
		waitpid(child_pid, &status, 0);
	if (!child_pid && execve(command_args[0], command_args, env) == -1)
	{
		minishell_error(strerror(errno), command_args[0]);
		exit(EX_USAGE);
	}
	return (WEXITSTATUS(status) == EX_USAGE ? 0 : 1);
}
