/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:12:36 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/08 04:37:24 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Write error message, eventually errno message, free variables and exit.
*/

void		error_exit(char *error_msg)
{
	char		*strerror_msg;

	write(2, error_msg, slen(error_msg));
	if (errno)
	{
		strerror_msg = strerror(errno);
		write(2, ": ", 2);
		write(2, strerror_msg, slen(strerror_msg));
	}
	write(2, "\n", 1);
	free_env();
	exit(EXIT_FAILURE);
}

void		minishell_error(char *error_msg, char *command)
{
	write(2, "Minishell: ", slen("Minishell: "));
	write(2, error_msg, slen(error_msg));
	write(2, ": ", 2);
	write(2, command, slen(command));
	write(2, "\n", 1);
}
