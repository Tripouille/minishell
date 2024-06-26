/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:12:36 by jgambard          #+#    #+#             */
/*   Updated: 2020/06/24 14:25:16 by aalleman         ###   ########lyon.fr   */
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

void		minishell_error(char *error_msg, char *command, int error)
{
	write(2, "Minishell: ", ft_strlen("Minishell: "));
	write(2, error_msg, ft_strlen(error_msg));
	if (*command)
	{
		write(2, ": ", 2);
		write(2, command, ft_strlen(command));
	}
	write(2, "\n", 1);
	g_status = error;
}

void		usage_error(char *command, char *error_msg, char *input, int error)
{
	ft_dprintf(2, "%s: %s", command, error_msg);
	if (*input)
		ft_dprintf(2, ": %s", input);
	write(2, "\n", 1);
	g_status = error;
}
