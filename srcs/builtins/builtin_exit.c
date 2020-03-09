/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 21:49:09 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/09 07:36:27 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_exit(char **args)
{
	free_command(args);
	free_env();
	system("leaks minishell");
	exit(EXIT_SUCCESS);
}
