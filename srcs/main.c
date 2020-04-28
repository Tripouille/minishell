/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:52:41 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/28 18:26:29 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				**env;
int					status;
t_lst				*commands;

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

	errno = 0;
	status = 0;
	commands = 0;
	initialize_env();
	initialize_builtins(builtins);
	while (1)
	{
		ask_for_command("PROMPT", buffer);
		//parse_buffer(buffer, builtins); //découper en commandes et arguments, demander les guillemets manquants
		parse_buffer(buffer);
		//run_commands();
		//ft_lst_purge(&commands, 0); //free_command = lst_purge(..., free) en 2nd parametre
	}
	return(0);
}
