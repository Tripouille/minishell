/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:26:08 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/01 19:40:50 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_echo(char **s)
{
	while (*s)
	{
		write(1, *s, slen(*s));
		s++;
	}
}

void		initialize_builtins(t_builtin builtins[])
{
	builtins[0].name = "echo";
	builtins[0].function = builtin_echo;
}
