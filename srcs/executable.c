/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 04:40:57 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/23 17:50:41 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_valid_path(char *command)
{
	char		**split;
	char		*path;
	int			i;
	struct stat	sb;

	if (!(split = ft_split(get_variable_value("PATH"), ':')))
		error_exit("Malloc fail");
	i = 0;
	while (split[i])
	{
		if (!(path = ft_strjoin(3, split[i], "/", command)))
		{
			free_str_array(split);
			error_exit("Malloc fail");
		}
		if (stat(path, &sb) == 0 && sb.st_mode & S_IXUSR)
		{
			free_str_array(split);
			return (path);
		}
		free(path);
		i++;
	}
	free_str_array(split);
	return (0);
}

/*
** Return 0 to display "command not found"
** if path is not valid or execve failed.
*/

int		launch_executable_in_path(char **command_args)
{
	int		child_pid;
	int		status;
	char	*path;

	if (!(path = get_valid_path(command_args[0])))
		return (0);
	child_pid = fork();
	if (child_pid)
		waitpid(child_pid, &status, 0);
	if (!child_pid && execve(path, command_args, env) == -1)
		exit(EX_USAGE);
	free(path);
	return (WEXITSTATUS(status) == EX_USAGE ? 0 : 1);
}

void	launch_executable(char **command_args)
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
}
