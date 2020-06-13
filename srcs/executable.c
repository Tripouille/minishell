/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 04:40:57 by jgambard          #+#    #+#             */
/*   Updated: 2020/06/13 18:42:09 by aalleman         ###   ########lyon.fr   */
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
	i = -1;
	while (split[++i])
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
	int			status;
	char		*path;
	char		**args_tab;
	struct stat	sb;

	if (stat(get_arg_value(args, 0), &sb) == 0 && sb.st_mode & S_IXUSR)
		path = ft_strdup(get_arg_value(args, 0));
	else if (!(path = get_valid_path(get_arg_value(args, 0))))
		return (0);
	fill_args_tab(&args_tab, args);
	g_child_pid = fork();
	if (!g_child_pid)
	{
		signal(SIGQUIT, SIG_DFL);
		if (execve(path, args_tab, g_env) == -1)
			exit(EX_USAGE);
	}
	waitpid(g_child_pid, &status, 0);
	g_child_pid = -1;
	free(path);
	free(args_tab);
	g_status = WIFEXITED(status) ? WEXITSTATUS(status) : g_status;
	return (WEXITSTATUS(status) == EX_USAGE ? 0 : 1);
}

void	launch_executable(t_lst *args)
{
	int		status;
	int		old_child_pid;
	char	**args_tab;

	fill_args_tab(&args_tab, args);
	old_child_pid = fork();
	if (old_child_pid)
		waitpid(old_child_pid, &status, 0);
	if (!old_child_pid && execve(get_arg_value(args, 0), args_tab, g_env) == -1)
	{
		minishell_error(strerror(errno), get_arg_value(args, 0), 1);
		exit(EX_USAGE);
	}
	free(args_tab);
	g_status = WEXITSTATUS(status);
}
