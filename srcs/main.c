/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:52:41 by jgambard          #+#    #+#             */
/*   Updated: 2020/05/01 19:33:55 by aalleman         ###   ########lyon.fr   */
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
	printf("\npipefd read : %d - write : %d\n\n", ((t_cmd_infos*)content)->pipefd[0], ((t_cmd_infos*)content)->pipefd[1]);
}

int		main(void)
{
	/*int		pipefd[2];
	char	b[100];

	pipe(pipefd);
	int save = dup(STDOUT_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	write(1, "lol", 3);
	close(pipefd[1]);
	dup2(save, STDOUT_FILENO);
	write(1, "abc", 3);*/
	
	char				buffer[BUFFER_SIZE];
	t_builtin			builtins[10];
	t_lst				*tmp_cmd;

	errno = 0;
	status = 0;
	commands = 0;
	*buffer = 0;
	initialize_env();
	initialize_builtins(builtins);
	while (1)
	{
		ask_for_command("PROMPT", buffer);
		parse_buffer(buffer);
		ft_lst_iter(commands, print_command);
		tmp_cmd = commands;
		while (tmp_cmd)
		{
			run_command(tmp_cmd->content, builtins);
			tmp_cmd = tmp_cmd->next;
		}
		ft_lst_purge(&commands, purge_cmd);
	}
	return(0);
}
