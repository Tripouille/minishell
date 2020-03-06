/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:52:41 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/06 04:18:12 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell_variable	*shell_variables;
char				**env;

int		main(void)
{
	//t_bool				waiting_for_command;
	//char				buffer[BUFFER_SIZE];
	//t_builtin			builtins[10];

	errno = 0;
	copy_environment();
	char	*test[2];
	test[1] = 0;
	//add_variable(ft_strdup("pouet=prout"));
	//del_variable("LC_ALL");
	builtin_env(test);
	//signal(2, SIG_IGN);
	//initialize_builtins(builtins);
	//initialize_shell_variables();
	//waiting_for_command = 1;
	//while (waiting_for_command)
	//{
		//ask_for_command("PROMPT", buffer);
		//parse_buffer(buffer, builtins);
	//}
	free_env();
	env = 0;
	system("leaks minishell");
	return(0);
}
