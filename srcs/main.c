/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:52:41 by jgambard          #+#    #+#             */
/*   Updated: 2020/06/08 10:32:34 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				**g_env;
int					g_status;
t_lst				*g_commands;
int					g_minishell_pid;
int					g_child_pid;

void	initialize(t_builtin builtins[], int fd_save[], char **envp)
{
	errno = 0;
	g_status = 0;
	g_child_pid = -1;
	g_commands = 0;
	initialize_env(envp);
	initialize_builtins(builtins);
	fd_save[IN] = dup(STDIN_FILENO);
	fd_save[OUT] = dup(STDOUT_FILENO);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

void	minishell(t_builtin builtins[], int fd_save[])
{
	char				buffer[BUFFER_SIZE];
	t_lst				*tmp_cmd;

	while (1)
	{
		if (ask_for_command("PROMPT", buffer, 0) == EOF)
			builtin_exit(0);
		split_redirections(buffer);
		if (parse_buffer(buffer) == 0)
		{
			tmp_cmd = g_commands;
			while (tmp_cmd)
			{
				g_child_pid = -1;
				if (handle_redirections(tmp_cmd->content) != -1)
					run_command(tmp_cmd->content, builtins, fd_save);
				else
					restore_fd(tmp_cmd->content, fd_save);
				tmp_cmd = tmp_cmd->next;
			}
		}
		ft_lst_purge(&g_commands, purge_cmd);
	}
}

int		main(int argc __attribute__((unused)),
				char **argv __attribute__((unused)), char **envp)
{
	t_builtin			builtins[10];
	int					fd_save[2];
	int					status;

	initialize(builtins, fd_save, envp);
	while (1)
	{
		g_minishell_pid = fork();
		if (g_minishell_pid)
			waitpid(g_minishell_pid, &status, 0);
		if (!g_minishell_pid)
		{
			signal(SIGINT, SIG_DFL);
			minishell(builtins, fd_save);
		}
		if (WIFEXITED(status))
			exit(WEXITSTATUS(status));
	}
	return (0);
}
