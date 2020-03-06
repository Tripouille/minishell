/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:52:41 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/06 06:50:56 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				**env;

int		main(void)
{
	t_bool				waiting_for_command;
	char				buffer[BUFFER_SIZE];
	t_builtin			builtins[10];

	errno = 0;
	//signal(2, SIG_IGN);
	initialize_env();
	initialize_builtins(builtins);
	waiting_for_command = 1;
	while (waiting_for_command)
	{
		ask_for_command("PROMPT", buffer);
		parse_buffer(buffer, builtins);
	}
	free_env();
	system("leaks minishell");
	return(0);
}
