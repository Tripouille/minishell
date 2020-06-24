/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:26:08 by jgambard          #+#    #+#             */
/*   Updated: 2020/06/24 18:11:45 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		initialize_env(char **envp)
{
	copy_environment(envp);
}

/*
** Initialize array of builtin names and functions.
*/

void		initialize_builtins(void)
{
	g_builtins[0].name = "echo";
	g_builtins[0].function = builtin_echo;
	g_builtins[1].name = "exit";
	g_builtins[1].function = builtin_exit;
	g_builtins[2].name = "env";
	g_builtins[2].function = builtin_env;
	g_builtins[3].name = "export";
	g_builtins[3].function = builtin_export;
	g_builtins[4].name = "unset";
	g_builtins[4].function = builtin_unset;
	g_builtins[5].name = "pwd";
	g_builtins[5].function = builtin_pwd;
	g_builtins[6].name = "cd";
	g_builtins[6].function = builtin_cd;
	g_builtins[7].name = 0;
	g_builtins[7].function = 0;
}
