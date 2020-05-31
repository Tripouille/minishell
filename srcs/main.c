/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:52:41 by jgambard          #+#    #+#             */
/*   Updated: 2020/05/31 13:53:49 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				**g_env;
int					g_status;
t_lst				*g_commands;

void	initialize(t_builtin builtins[], int fd_save[], char **envp)
{
	errno = 0;
	g_status = 0;
	g_commands = 0;
	initialize_env(envp);
	initialize_builtins(builtins);
	fd_save[IN] = dup(STDIN_FILENO);
	fd_save[OUT] = dup(STDOUT_FILENO);
}

int		main(int argc __attribute__((unused)),
				char **argv __attribute__((unused)), char **envp)
{
	char				buffer[BUFFER_SIZE];
	t_builtin			builtins[10];
	t_lst				*tmp_cmd;
	int					fd_save[2];

	initialize(builtins, fd_save, envp);
	while (1)
	{
		ask_for_command("PROMPT", buffer, 0);
		if (parse_buffer(buffer) == 0)
		{
			tmp_cmd = g_commands;
			while (tmp_cmd)
			{
				if (handle_redirections(tmp_cmd->content) != -1)
					run_command(tmp_cmd->content, builtins, fd_save);
				tmp_cmd = tmp_cmd->next;
			}
		}
		ft_lst_purge(&g_commands, purge_cmd);
	}
	return (0);
}
