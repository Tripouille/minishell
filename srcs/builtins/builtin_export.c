/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 01:26:25 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/24 15:47:51 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_export(char **args)
{
	char		buffer[100];
	
	if (!args[1])
		return (builtin_env(args));
	while (*++args)
	{
		if (**args == '=')
			minishell_error("bad assignment", "");
		else if (!is_identifier(*args))
		{
			ft_strccpy(buffer, *args, '=');
			usage_error("export", "not an identifier", buffer);
		}
		else
			set_variable(*args);
	}
	status = SUCCESS_STATUS;
}
