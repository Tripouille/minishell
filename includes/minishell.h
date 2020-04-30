/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:48:55 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/30 18:19:24 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//LINUX
#include <sys/types.h>
#include <sys/wait.h>
//LINUX

# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <linux/limits.h>
# include <sysexits.h>
# include <sys/stat.h>
# include "libft.h"

# define PROMPT "Minishell: "
# define NOT_EXPORTED 0
# define EXPORTED 1
# define SUCCESS_STATUS 0
# define ERROR_STATUS 1
# define COMMAND_NOT_FOUND "command not found"
# define UNKNOWN_PARAMETER "unknown parameter"
# define TOO_MANY_ARGUMENTS "too many arguments"
# define MISSING_ARGUMENT "missing argument"
# define BUFFER_SIZE 10000

# define RESET "\033[0m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"

typedef char		t_bool;
typedef void		(*t_function)(char **av);

typedef struct		s_cmd_infos
{
	t_lst					*args;
	int						pipefd[2];
	struct s_cmd_infos		*next;
}					t_cmd_infos;

typedef struct		s_builtin
{
	char			*name;
	t_function		function;
}					t_builtin;

extern char					**environ;
extern char					**env;
extern int					status;
extern t_lst*				commands;

void				error_exit(char *error_msg);
void				minishell_error(char *error_msg, char *command);

void				initialize_builtins(t_builtin builtins[]);
void				initialize_env(void);

void				builtin_echo(char **args);
void				builtin_exit(char **args);
void				builtin_env(char **args);
void				builtin_export(char **args);
void				builtin_unset(char **args);
void				builtin_pwd(char **args);
void				builtin_cd(char **args);

void				ask_for_command(char *prompt_name, char *buffer);
void				parse_buffer(char *buffer);

int					count_args(char *buffer);
void				fill_command_args(char **buffer, char **command_args);

void				purge_cmd(void *cmd_infos);
char				*wait_for_rest(char *buffer, char quote);
int					arg_len(char *buffer);
void				replace_variable(char **buffer, char *arg, int *i);

void				copy_environment(void);
void				free_env(void);

void				del_variable(char *variable_name);
void				add_variable(char *variable);
void				set_variable(char *variable);

int					is_identifier(char *str);
char				*get_variable_value(char *variable_name);
int					variable_name_len(char *buffer);
int					variable_comp(char *s1, char *s2);
int					get_variable_pos(char *variable_name);
void				usage_error(char *command, char *error_msg, char *input);

int					tab_size(char **tab);

void				launch_executable(char **command_args);
int					launch_executable_in_path(char **command_args);

#endif
