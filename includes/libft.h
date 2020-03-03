/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:48:40 by jgambard          #+#    #+#             */
/*   Updated: 2020/03/03 23:21:32 by jgambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

size_t				slen(const char *s);
int					ft_isdigit(int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
size_t				ft_strlcpy(char *dst, const char *rsc, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
int					ft_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s1);
double				square(double x);
int					cinstr(char c, char *str);
void				skip_spaces(void *buffer, int *i);

#endif
