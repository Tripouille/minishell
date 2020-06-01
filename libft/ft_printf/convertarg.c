/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertarg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:29 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/23 18:37:55 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Gets minimum field width with next digits or from argument if *.
*/

int		getminwidth(char **s, int *options, va_list va)
{
	if (**s == '*')
	{
		options[MW] = va_arg(va, int);
		if (options[MW] < 0)
		{
			options[LEFT] = 1;
			options[MW] *= options[MW] == INT_MIN ? 0 : -1;
		}
		++*s;
	}
	else
	{
		options[MW] = ft_atoi_printf(*s);
		skip_digits(s);
	}
	return (1);
}

/*
** If there is a point, gets accuracy with next digits or from argument if *.
*/

void	getaccuracy(char **s, int *options, va_list va)
{
	if (**s == '.')
	{
		++*s;
		if (**s == '*')
		{
			options[ACC] = va_arg(va, int);
			++*s;
		}
		else
		{
			options[ACC] = ft_atoi_printf(*s);
			skip_digits(s);
		}
	}
}

/*
** Sets options[LM] to the correct length modifier.
*/

void	getlengthmodifier(char **s, int *options)
{
	options[LM] = 0;
	if (!ft_strncmp(*s, "ll", 2))
	{
		options[LM] = LL;
		*s += 2;
	}
	else if (**s == 'l')
	{
		options[LM] = L;
		++*s;
	}
	else if (!ft_strncmp(*s, "hh", 2))
	{
		options[LM] = HH;
		*s += 2;
	}
	else if (**s == 'h')
	{
		options[LM] = H;
		++*s;
	}
}

/*
** Sets default values then fills an option array with
** attributes, minimum field width, accuracy and length modifier
** Attribute 0 (ZERO) is removed if there is option - (LEFT).
*/

int		getoptions(char **s, int *options, va_list va)
{
	int		i;

	i = 0;
	while (i < (int)ft_strlen(FLAGS))
		options[i++] = 0;
	options[ACC] = -1;
	while (**s && (i = cinstr(FLAGS, **s)) >= 0)
	{
		options[i] = 1;
		++*s;
	}
	if (getminwidth(s, options, va) == -1)
		return (-1);
	getaccuracy(s, options, va);
	getlengthmodifier(s, options);
	options[ZERO] = options[LEFT] ? 0 : options[ZERO];
	return (1);
}

/*
** Retrieves options of conversion and uses the associated function on argument.
*/

char	*convertarg(char **s, va_list va, t_dict *dict, int *options)
{
	int			i;

	if (getoptions(s, options, va) == -1)
		return (0);
	i = 0;
	while (dict[i].c)
	{
		if (**s == dict[i].c)
		{
			if (cinstr(NUMERICFORMAT, **s) != -1)
				if (options[ACC] >= 0)
					options[ZERO] = 0;
			++*s;
			return (dict[i].fnct(va, options));
		}
		i++;
	}
	return (0);
}
