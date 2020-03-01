/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:52:41 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/01 19:33:57 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(void)
{
	t_bool		waiting_for_command;
	char		buffer[BUFFER_SIZE];
	int			read_ret;
	t_builtin	builtins[10];

	errno = 0;
	initialize_builtins(builtins);
	waiting_for_command = 1;
	while (waiting_for_command)
	{
		write(1, PROMPT, slen(PROMPT));
		if ((read_ret = read(0, buffer, BUFFER_SIZE)) == -1)
			error_exit("Read error: ");
		buffer[read_ret] = 0;
		if (strcmp(buffer, "exit\n") == 0)
			waiting_for_command = 0;
		write(1, buffer, read_ret);
	}
	builtins[0].function((char**)0);
	return(0);
}
