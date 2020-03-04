/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:26:08 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/04 04:21:04 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Initialize shell variables with prompts.
*/

void		initialize_shell_variables(void)
{
	shell_variables = 0;
	add_variable(ft_strdup("PROMPT"), ft_strdup("YOLO: "), NOT_EXPORTED);
	add_variable(ft_strdup("PROMPT_QUOTE"), ft_strdup("quote> "), NOT_EXPORTED);
	add_variable(ft_strdup("PROMPT_DQUOTE"), ft_strdup("dquote> "), NOT_EXPORTED);
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
	builtins[6].name = 0;
}
