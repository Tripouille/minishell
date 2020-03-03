/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:52:41 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/03 01:34:33 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell_variable	*shell_variables;

int		main(void)
{
	t_bool				waiting_for_command;
	char				buffer[BUFFER_SIZE];
	int					read_ret;
	t_builtin			builtins[10];
	char				*prompt_value;

	errno = 0;
	signal(2, SIG_IGN);
	initialize_builtins(builtins);
	initialize_shell_variables();
	waiting_for_command = 1;
	while (waiting_for_command)
	{
		if ((prompt_value = get_variable_value("PROMPT")))
			write(1, prompt_value, slen(prompt_value));
		if ((read_ret = read(0, buffer, BUFFER_SIZE)) == -1)
			error_exit("Read error");
		buffer[read_ret] = 0;
		parse_buffer(buffer, builtins);
	}
	return(0);
}
