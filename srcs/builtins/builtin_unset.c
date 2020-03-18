/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 02:26:52 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/18 20:07:13 by jgambard         ###   ########.fr       */
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
