/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 04:40:57 by jgambard          #+#    #+#             */
/*   Updated: 2020/05/31 16:18:49 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_args_tab(char ***args_tab, t_lst *args)
{
	int		i;

	if (!(*args_tab = ft_calloc(ft_lst_size(args) + 1, sizeof(char*))))
		error_exit("Malloc fail");
	i = 0;
	while (args)
	{
		(*args_tab)[i++] = get_arg_value(args, 0);
		args = args->next;
	}
}

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

int		launch_executable_in_path(t_lst *args)
{
	int		child_pid;
	int		status;
	char	*path;
	char	**args_tab;

	if (!(path = get_valid_path(get_arg_value(args, 0))))
		return (0);
	fill_args_tab(&args_tab, args);
	child_pid = fork();
	if (child_pid)
		waitpid(child_pid, &status, 0);
	if (!child_pid && execve(path, args_tab, g_env) == -1)
		exit(EX_USAGE);
	free(path);
	free(args_tab);
	return (WEXITSTATUS(status) == EX_USAGE ? 0 : 1);
}

void	launch_executable(t_lst *args)
{
	int		child_pid;
	int		status;
	char	**args_tab;

	fill_args_tab(&args_tab, args);
	child_pid = fork();
	if (child_pid)
		waitpid(child_pid, &status, 0);
	if (!child_pid && execve(get_arg_value(args, 0), args_tab, g_env) == -1)
	{
		minishell_error(strerror(errno), get_arg_value(args, 0));
		exit(EX_USAGE);
	}
	free(args_tab);
}
