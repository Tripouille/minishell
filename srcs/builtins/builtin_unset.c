/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 02:26:52 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/23 18:37:55 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_unset(char **args)
{
	if (!args[1])
	{
		write(2, args[0], ft_strlen(args[0]));
		write(2, ": ", 2);
		write(2, MISSING_ARGUMENT, ft_strlen(MISSING_ARGUMENT));
		write(2, "\n", 1);
		status = ERROR_STATUS;
		return ;
	}
	while (*++args)
		del_variable(*args);
	status = SUCCESS_STATUS;
}
