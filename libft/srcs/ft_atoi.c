/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:57:04 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 12:57:10 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int					ft_atoi(const char *str)
{
	int		result;
	int		minus;

	result = 0;
	minus = 0;
	while (str && ((*str >= 9 && *str <= 13) || *str == ' '))
		str++;
	if (*str == '-' || *str == '+')
		minus += (*str++ == '-' ? 1 : 0);
	while (*str >= '0' && *str <= '9')
		result = (result * 10) + (*str++ - '0');
	return (result * (minus % 2 ? -1 : 1));
}
