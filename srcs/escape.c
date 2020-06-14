/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 16:08:00 by aalleman          #+#    #+#             */
/*   Updated: 2020/06/14 15:03:23 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_backslash_len(char **buffer, char quote)
{
	(*buffer)++;
	if (quote && cinstr(SPECIAL_CHARACTERS, **buffer) == -1)
		return (2);
	else
		return (1);
}

void	handle_backslash(char **buffer, char *arg, int *i, char quote)
{
	(*buffer)++;
	if (quote && cinstr(SPECIAL_CHARACTERS, **buffer) == -1)
		arg[(*i)++] = '\\';
	arg[(*i)++] = **buffer;
}
