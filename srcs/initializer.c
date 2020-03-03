/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:26:08 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/03 02:02:37 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		initialize_shell_variables(void)
{
	shell_variables = 0;
	add_variable(ft_strdup("PROMPT"), ft_strdup("YOLO: "), NOT_EXPORTED);
}

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
	builtins[4].name = 0;
}
