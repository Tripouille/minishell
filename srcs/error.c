/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:12:36 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/18 19:52:00 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Write error message, eventually errno message, free variables and exit.
*/

void		error_exit(char *error_msg)
{
	char		*strerror_msg;

	write(2, error_msg, ft_strlen(error_msg));
	if (errno)
	{
		strerror_msg = strerror(errno);
		write(2, ": ", 2);
		write(2, strerror_msg, ft_strlen(strerror_msg));
	}
	write(2, "\n", 1);
	free_env();
	exit(EXIT_FAILURE);
}

void		minishell_error(char *error_msg, char *command)
{
	write(2, "Minishell: ", ft_strlen("Minishell: "));
	write(2, error_msg, ft_strlen(error_msg));
	write(2, ": ", 2);
	write(2, command, ft_strlen(command));
	write(2, "\n", 1);
}
