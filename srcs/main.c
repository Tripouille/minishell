/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:52:41 by jgambard          #+#    #+#             */
/*   Updated: 2020/05/03 20:36:40 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				**env;
int					status;
t_lst				*commands;

void	print_args(void *arg)
{
	printf("[%s] / ", (char*)arg);
}

void	print_command(void *content)
{
	ft_lst_iter(((t_cmd_infos*)content)->args, print_args);
	printf("\npipefd read : %d - write : %d\n\n", ((t_cmd_infos*)content)->fd[0], ((t_cmd_infos*)content)->fd[1]);
}

void	initialize(t_builtin builtins[], int fd_save[])
{
	errno = 0;
	status = 0;
	commands = 0;
	initialize_env();
	initialize_builtins(builtins);
	fd_save[IN] = dup(STDIN_FILENO);
	fd_save[OUT] = dup(STDOUT_FILENO);
}

int		main(void)
{
	char				buffer[BUFFER_SIZE];
	t_builtin			builtins[10];
	t_lst				*tmp_cmd;
	int					fd_save[2];

	initialize(builtins, fd_save);
	while (1)
	{
		ask_for_command("PROMPT", buffer);
		parse_buffer(buffer);
		//ft_lst_iter(commands, print_command);
		tmp_cmd = commands;
		while (tmp_cmd)
		{
			run_command(tmp_cmd->content, builtins, fd_save);
			tmp_cmd = tmp_cmd->next;
		}
		ft_lst_purge(&commands, purge_cmd);
	}
	return(0);
}
