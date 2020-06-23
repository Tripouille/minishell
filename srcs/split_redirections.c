/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 10:33:11 by aalleman          #+#    #+#             */
/*   Updated: 2020/06/23 19:39:03 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shifteuse(char *buffer, int i)
{
	int		j;

	if (!i)
		return ;
	j = ft_strlen(buffer);
	buffer[j + 1] = 0;
	while (j > i)
	{
		buffer[j] = buffer[j - 1];
		j--;
	}
	buffer[i] = ' ';
}

t_bool	is_escaped(char *buffer, int i)
{
	int		escape;

	escape = 0;
	while (i-- && buffer[i] == '\\')
		escape++;
	return (escape % 2);
}

void	split_redirections(char *buffer)
{
	int		i;
	int		quote;

	quote = 0;
	i = -1;
	while (buffer[++i] && (!i || buffer[i - 1]))
	{
		if (quote && buffer[i] == quote)
			quote = 0;
		else if (!quote && cinstr("'\"", buffer[i]) != -1)
			quote = buffer[i];
		if (!quote && !is_escaped(buffer, i) && cinstr("><", buffer[i]) != -1
		&& (!i || buffer[i - 1] != buffer[i] || is_escaped(buffer, i - 1))
		&& (!i || buffer[i - 1] != ' '))
			shifteuse(buffer, i);
	}
}
