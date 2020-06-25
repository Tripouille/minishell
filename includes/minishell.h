/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:48:55 by jgambard          #+#    #+#             */
/*   Updated: 2020/06/24 20:08:38 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <linux/limits.h>
# include <sysexits.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"

# define PROMPT "Minishell "
# define PROMPT_QUOTE ">quote "
# define PROMPT_DQUOTE ">dquote "
# define PROMPT_PIPE ">pipe "
# define NOT_EXPORTED 0
# define EXPORTED 1
# define SUCCESS_STATUS 0
# define ERROR_STATUS 1
# define COMMAND_NOT_FOUND "command not found"
# define UNKNOWN_PARAMETER "unknown parameter"
# define TOO_MANY_ARGUMENTS "too many arguments"
# define MISSING_ARGUMENT "missing argument"
# define BUFFER_SIZE 10000
# define SPECIAL_CHARACTERS "\"$\\"

# define RESET "\033[0m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"

# define IN 0
# define OUT 1

enum {FALSE, TRUE};

typedef char		t_bool;
typedef void		(*t_function)(t_lst *args);

typedef struct		s_argument
{
	char			*s;
	t_bool			quoted;
}					t_argument;

typedef struct		s_cmd_infos
{
	t_lst					*args;
	int						fd[2];
}					t_cmd_infos;

typedef struct		s_builtin
{
	char			*name;
	t_function		function;
}					t_builtin;

extern char					**g_environ;
extern char					**g_env;
extern int					g_status;
extern t_lst*				g_commands;
extern int					g_minishell_pid;
extern int					g_child_pid;
extern int					g_fd_save[2];
t_builtin					g_builtins[10];

void				error_exit(char *error_msg);
void				minishell_error(char *error_msg, char *command, int error);
void				usage_error(char *command, char *error_msg, char *input,
									int error);

void				initialize_builtins(void);
void				initialize_env(char **envp);

void				builtin_echo(t_lst *args);
void				ft_exit(long ret, int display);
void				builtin_exit(t_lst *args);
void				builtin_env(t_lst *args);
void				builtin_export(t_lst *args);
void				builtin_unset(t_lst *args);
void				builtin_pwd(t_lst *args);
void				builtin_cd(t_lst *args);

int					ask_for_command(char *prompt_name, char *buffer, int pos,
										int first_call);
int					check_buffer(char *buffer);
int					check_buffer2(char *buffer, int *i, char *quote,
									char *last_char);

t_function			get_builtins_fct(char *cmd_name);
void				run_command(t_cmd_infos *cmd_infos);
char				*get_cmd_name(t_cmd_infos *cmd_infos);
void				destroy_arg(void *arg);

int					parse_buffer(char *buffer);
int					handle_command(char **buffer, t_lst **command,
									t_cmd_infos **cmd_infos);
int					fill_args(char **buffer, t_lst **args);

void				handle_argument(char **buffer, int arg_length,
									t_lst **args);
void				calloc_arg(t_argument **arg, int arg_length);
void				format_arg(char **buffer, char *arg);

void				handle_backslash(char **buffer, char *arg, int *i,
										char quote);
int					get_backslash_len(char **buffer, char quote);

char				*get_arg_value(t_lst *args, int pos);
void				purge_cmd(void *cmd_infos);
int					arg_len(char *buffer);
void				replace_variable(char **buffer, char *arg, int *i);

void				copy_environment(char **envp);
void				free_env(void);

void				del_variable(char *variable_name);
void				add_variable(char *variable);
void				set_variable(char *variable, int concatenate);

int					is_identifier(char *str);
char				*get_variable_value(char *variable_name);
int					variable_name_len(char *buffer);
int					variable_comp(char *s1, char *s2);
int					get_variable_pos(char *variable_name);

int					tab_size(char **tab);

void				launch_executable(t_lst *args);
int					launch_executable_in_path(t_lst *args);

void				synchronize_fd(t_cmd_infos *cmd_infos);
void				restore_fd(t_cmd_infos *cmd_infos);

int					handle_redirections(t_cmd_infos *cmd_infos);

void				split_redirections(char *buffer);
t_bool				is_escaped(char *buffer, int i);

t_bool				invalid_redirection(void);

void				sigint_handler(int signal);
void				sigquit_handler(int signal);

#endif
