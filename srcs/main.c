/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 14:47:40 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/29 15:31:04 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(void)
{
	t_bool		running;
	char		buffer[BUFFER_SIZE];
	int			read_ret;

	running = 1;
	while (running)
	{
		write(1, PROMPT, slen(PROMPT));
		if ((read_ret = read(0, buffer, BUFFER_SIZE)) == -1)
			exit(EXIT_FAILURE); //ecrire erreur
		buffer[read_ret] = 0;
		if (strcmp(buffer, "exit\n") == 0)
			running = 0;
		write(1, buffer, read_ret);
	}
	return(0);
}
