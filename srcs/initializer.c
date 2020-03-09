/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:26:08 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/09 06:21:09 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		initialize_env(void)
{
	copy_environment();
	set_variable("PROMPT=Kernel ");
	set_variable("PROMPT_QUOTE=quote> ");
	set_variable("PROMPT_DQUOTE=dquote> ");
}

/*
** Initialize array of builtin names and functions.
*/

void		initialize_builtins(t_builtin builtins[])
{
	builtins[0].name = "echo";
	builtins[0].function = builtin_echo;
	builtins[1].name = "exit";
	builtins[1].function = builtin_exit;
	builtins[2].name = "env";
	builtins[2].function = builtin_env;
	builtins[3].name = "export";
	builtins[3].function = builtin_export;
	builtins[4].name = "unset";
	builtins[4].function = builtin_unset;
	builtins[5].name = "pwd";
	builtins[5].function = builtin_pwd;
	builtins[6].name = "cd";
	builtins[6].function = builtin_cd;
	builtins[7].name = 0;
}
