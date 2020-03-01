/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:48:55 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/01 21:55:44 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include "libft.h"

# define PROMPT "Minishell: "
# define COMMAND_NOT_FOUND ": command not found\n"
# define BUFFER_SIZE 10000

typedef char		t_bool;
typedef void		(*t_function)(char **av);

typedef struct		s_builtin
{
	char			*name;
	t_function		function;
}					t_builtin;

void		error_exit(char *error_msg);

void		initialize_builtins(t_builtin builtins[]);

void		builtin_echo(char **s);
void		builtin_exit(char **s);

void		parse_buffer(char *buffer, t_builtin builtins[]);

void		parse_command(char **buffer, char ***command_args);
void		free_command(char **command_args);
#endif
