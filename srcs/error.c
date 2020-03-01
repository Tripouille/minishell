/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:12:36 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/01 19:23:30 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		error_exit(char *error_msg)
{
	char		*strerror_msg;

	write(2, error_msg, slen(error_msg));
	if (errno)
	{
		strerror_msg = strerror(errno);
		write(2, strerror_msg, slen(strerror_msg));
	}
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}
