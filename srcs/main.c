/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:52:41 by jgambard          #+#    #+#             */
/*   Updated: 2020/06/24 19:27:01 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				**g_env;
int					g_status;
t_lst				*g_commands;
int					g_child_pid;
int					g_fd_save[2];
t_builtin			g_builtins[10];

void	initialize(char **envp)
{
	errno = 0;
	g_status = 0;
	g_child_pid = -1;
	g_commands = 0;
	initialize_env(envp);
	initialize_builtins();
	g_fd_save[IN] = dup(STDIN_FILENO);
	g_fd_save[OUT] = dup(STDOUT_FILENO);
	signal(SIGQUIT, sigquit_handler);
	signal(SIGINT, sigint_handler);
}

void	minishell(void)
{
	char				buffer[BUFFER_SIZE];
	t_lst				*tmp_cmd;

	while (1)
	{
		if (ask_for_command(PROMPT, buffer, 0, 1) == -1)
			continue ;
		split_redirections(buffer);
		if (parse_buffer(buffer) == 0 && invalid_redirection() == 0)
		{
			tmp_cmd = g_commands;
			while (tmp_cmd)
			{
				g_child_pid = -1;
				if (((t_cmd_infos*)tmp_cmd->content)->args
				&& handle_redirections(tmp_cmd->content) != -1)
					run_command(tmp_cmd->content);
				else
					restore_fd(tmp_cmd->content);
				tmp_cmd = tmp_cmd->next;
			}
		}
		ft_lst_purge(&g_commands, purge_cmd);
	}
}

int		main(int argc __attribute__((unused)),
				char **argv __attribute__((unused)), char **envp)
{
	initialize(envp);
	minishell();
	return (0);
}
