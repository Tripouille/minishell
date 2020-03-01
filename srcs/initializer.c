/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:26:08 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/01 21:55:15 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		initialize_builtins(t_builtin builtins[])
{
	builtins[0].name = "echo";
	builtins[0].function = builtin_echo;
	builtins[1].name = "exit";
	builtins[1].function = builtin_exit;
	builtins[2].name = 0;
}
