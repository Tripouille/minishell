/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 01:26:25 by jgambard          #+#    #+#             */
/*   Updated: 2020/06/13 18:13:35 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap(char **p1, char **p2)
{
	char	*tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

char	**alphabet_sort(char **env)
{
	char	**sorted_env;
	int		i;
	int		j;
	int		m;

	if (!(sorted_env = ft_calloc(str_array_size(env) + 1, sizeof(char*))))
		error_exit("Malloc failed");
	i = -1;
	while (env[++i])
		sorted_env[i] = env[i];
	sorted_env[i] = 0;
	i = -1;
	while (sorted_env[++i])
	{
		m = i;
		j = i;
		while (sorted_env[++j])
			if (ft_strcmp(sorted_env[m], sorted_env[j]) > 0)
				m = j;
		if (m != i)
			swap(sorted_env + i, sorted_env + m);
	}
	return (sorted_env);
}

void	show_variables(void)
{
	char		**variable;
	char		var_name[1000];
	int			i;
	char		**sorted_env;

	g_status = SUCCESS_STATUS;
	sorted_env = alphabet_sort(g_env);
	variable = sorted_env;
	while (*variable)
	{
		i = 0;
		while ((*variable)[i] && (*variable)[i] != '=')
		{
			var_name[i] = (*variable)[i];
			i++;
		}
		var_name[i] = 0;
		ft_printf("declare -x %s=\"%s\"\n", var_name,
					get_variable_value(var_name));
		variable++;
	}
	free(sorted_env);
}

void	builtin_export(t_lst *args)
{
	char		buffer[1000];

	g_status = SUCCESS_STATUS;
	if (!args->next)
		return (show_variables());
	while ((args = args->next))
	{
		if (get_arg_value(args, 0)[0] == '=')
			minishell_error("bad assignment", "", 1);
		else if (!is_identifier(get_arg_value(args, 0)))
		{
			ft_strccpy(buffer, get_arg_value(args, 0), '=');
			usage_error("export", "not an identifier", buffer, 1);
		}
		else
			set_variable(get_arg_value(args, 0));
	}
}
