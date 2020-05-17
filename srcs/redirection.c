/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 05:41:57 by aalleman          #+#    #+#             */
/*   Updated: 2020/05/17 08:50:26 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_file_name_and_move_arg(char *file_name, t_lst **arg, t_lst **head, int offset)
{
	t_lst		*next;
	
	if (((char*)((*arg)->content))[offset])
		ft_strlcpy(file_name, (char*)((*arg)->content) + offset, PATH_MAX + 1);
	else //gerer cas où < dernier arg
	{
		ft_strlcpy(file_name, (char*)((*arg)->next->content), PATH_MAX + 1);
		ft_lst_remove(head, (*arg)->next, free);
	}
	next = (*arg)->next;
	ft_lst_remove(head, *arg, free);
	*arg = next;
}

int		append_redirection(t_cmd_infos *cmd_infos, t_lst **arg)
{
	int		fd;
	char	file_name[PATH_MAX + 1];
	
	set_file_name_and_move_arg(file_name, arg, &cmd_infos->args, 2);
	if ((fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0664)) == -1)
	{
		minishell_error("Couldn't open file", file_name);
		return (-1);
	}
	else
		cmd_infos->fd[OUT] = fd;
	return (0);
}

int		replace_redirection(t_cmd_infos *cmd_infos, t_lst **arg)
{
	int		fd;
	char	file_name[PATH_MAX + 1];
	
	set_file_name_and_move_arg(file_name, arg, &cmd_infos->args, 1);
	if ((fd = open(file_name, O_WRONLY | O_CREAT, 0664)) == -1)
	{
		minishell_error("Couldn't open file", file_name);
		return (-1);
	}
	else
		cmd_infos->fd[OUT] = fd;
	return (0);
}

int		read_redirection(t_cmd_infos *cmd_infos, t_lst **arg)
{
	int		fd;
	char	file_name[PATH_MAX + 1];
	
	set_file_name_and_move_arg(file_name, arg, &cmd_infos->args, 1);
	if ((fd = open(file_name, O_RDONLY)) == -1)
	{
		minishell_error("Couldn't open file", file_name);
		return (-1);
	}
	else
		cmd_infos->fd[IN] = fd;
	return (0);
}

int		handle_redirections(t_cmd_infos *cmd_infos)
{
	t_lst		*arg;

	arg = cmd_infos->args;
	while (arg)
	{
		if (ft_strncmp(">>", arg->content, 2) == 0)
		{
			if (append_redirection(cmd_infos, &arg) == -1)
				return (-1);
		}
		else if (((char*)(arg->content))[0] == '>')
		{
			if (replace_redirection(cmd_infos, &arg) == -1)
				return (-1);
		}
		else if (((char*)(arg->content))[0] == '<')
		{
			if (read_redirection(cmd_infos, &arg) == -1)
				return (-1);
		}
		else
			arg = arg->next;
	}
	return (0);
}