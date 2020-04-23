/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:52:41 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/23 17:37:57 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				**env;
int					status;

int		main(void)
{
	char				buffer[BUFFER_SIZE];
	t_builtin			builtins[10];

	errno = 0;
	status = 0;
	initialize_env();
	initialize_builtins(builtins);
	while (1)
	{
		ask_for_command("PROMPT", buffer);
		parse_buffer(buffer, builtins); //découper en commandes et arguments, demander les guillemets manquants
		//run_commands();
	}
	return(0);
}
