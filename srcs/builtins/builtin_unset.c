/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 02:26:52 by jgambard          #+#    #+#             */
/*   Updated: 2020/06/02 16:29:40 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_unset(t_lst *args)
{
	g_status = SUCCESS_STATUS;
	while ((args = args->next))
		del_variable(get_arg_value(args, 0));
}
