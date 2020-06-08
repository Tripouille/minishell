/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 10:33:11 by aalleman          #+#    #+#             */
/*   Updated: 2020/06/08 11:05:46 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_redirections(char *buffer)
{
	int		i;
	int		j;

	i = -1;
	while (buffer[++i])
	{
		if ((cinstr(">< \\", buffer[i]) == -1
		&& buffer[i + 1] && cinstr("><", buffer[i + 1]) != -1)
		|| (i && !ft_strncmp("\\>>", buffer + i - 1, 3))
		|| (i && !ft_strncmp("\\<<", buffer + i - 1, 3)))
		{
			j = ft_strlen(buffer);
			buffer[j + 1] = 0;
			while (j > i + 1)
			{
				buffer[j] = buffer[j - 1];
				j--;
			}
			buffer[i + 1] = ' ';
		}
	}
}
