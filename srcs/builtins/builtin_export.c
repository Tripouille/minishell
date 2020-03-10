/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 01:26:25 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/10 03:45:22 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_export(char **args)
{
	if (!args[1])
		return (builtin_env(args));
	while (*++args)
	{
		if (cinstr('=', *args) != -1)
			set_variable(*args);
	}
	status = SUCCESS_STATUS;
}
