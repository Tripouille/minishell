/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:02:29 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 13:02:32 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	setdict(t_dict *dict, char c, t_fput fnct)
{
	dict->c = c;
	dict->fnct = fnct;
}

/*
** Fills the dictionnary with a conversion character
** and its associated function pointer.
*/

void	initdict(t_dict *dict)
{
	setdict(dict, 'c', &getcharac);
	setdict(dict + 1, 's', &getstr);
	setdict(dict + 2, 'd', &geti);
	setdict(dict + 3, 'i', &geti);
	setdict(dict + 4, 'o', &geto);
	setdict(dict + 5, 'u', &getu);
	setdict(dict + 6, 'x', &getx);
	setdict(dict + 7, 'X', &getux);
	setdict(dict + 8, 'p', &getp);
	setdict(dict + 9, '%', &getpercent);
	setdict(dict + 10, 'n', &setn);
	setdict(dict + 11, 'f', &getf);
	setdict(dict + 12, 'e', &gete);
	setdict(dict + 13, 'g', &getg);
	setdict(dict + 14, 0, 0);
}
