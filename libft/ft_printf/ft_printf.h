/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 18:09:03 by jgambard          #+#    #+#             */
/*   Updated: 2020/04/23 18:37:55 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include "base.h"
# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define NUMERICFORMAT "diouxX"
# define FLAGS "0-# +'"
# define OPTIONS_NB 10

enum				{ZERO, LEFT, SHARP, SPACE, PLUS, APOS};
enum				{MW = 6, ACC, LM, TOTAL_SIZE};
enum				{HH = -2, H = -1, L = 1, LL = 2};
enum				{CHAR, SINT, INT, LONG, LLONG};
enum				{UCHAR = 5, USINT, UINT, ULONG, ULLONG};

typedef char		t_bool;

typedef char		*(*t_fput)(va_list va, int* options);

typedef struct		s_dict
{
	char			c;
	t_fput			fnct;
}					t_dict;

typedef struct		s_list
{
	char			*b;
	int				b_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_nbinfos
{
	void			*nb;
	int				pow;
	int				len;
	t_bool			neg;
}					t_nbinfos;

int					ft_printf(const char *s, ...)
					 __attribute__((format(printf,1,2)));

void				setdict(t_dict *dict, char c, t_fput fnct);
void				initdict(t_dict *dict);

int					list_add(t_list **begin, void *s, int size);
int					list_clear(t_list **begin);
int					fill_list(t_list **begin, char *s, va_list va,
								t_dict *dict);
void				print_list(t_list *begin);

int					getminwidth(char **s, int *options, va_list va);
void				getaccuracy(char **s, int *options, va_list va);
void				getlengthmodifier(char **s, int *options);
int					getoptions(char **s, int *options, va_list va);
char				*convertarg(char **s, va_list va, t_dict *dict,
									int *options);

char				*collectchars(char **s, int *len);
char				*getcharac(va_list va, int *options);
char				*getstr(va_list va, int *options);
char				*getpercent(va_list va, int *options);

char				*geti(va_list va, int *options);
char				*getu(va_list va, int *options);
char				*getx(va_list va, int *options);
char				*getux(va_list va, int *options);
char				*getp(va_list va, int *options);

void				write_sign(char *s, t_nbinfos *infos, int *options);
void				write_int_w_commas(char *s, t_nbinfos *infos,
								int base, int *options);
void				write_basic_number(char *s, unsigned long long nb,
								int base, int pow);
void				write_integer(char *s, t_nbinfos *infos, int base,
									int *options);
void				write_0x(char *s, t_nbinfos *infos, int *options);

int					fillwc(char *s, int width, char c);
char				*ft_toupper(char *s);
void				skip_digits(char **s);

int					ft_atoi_printf(const char *str);
int					max_pow(unsigned long long nb, unsigned long long base);

void				ft_strncpy(char *dest, const char *src, size_t size);
int					cinstr(char *str, char c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

void				*getarg(void *nb, va_list va, int *options, int size);

char				*getf(va_list va, int *options);
char				*gete(va_list va, int *options);
char				*getg(va_list va, int *options);
void				getgf(char **s, t_nbinfos *infos, int *options);
void				getge(char **s, t_nbinfos *infos, int *options);

char				*setn(va_list va, int *options);

void				write_f(char *s, t_nbinfos *infos, int *options);
void				write_e(char *s, t_nbinfos *infos, int *options);
char				*mallouc_double(t_nbinfos *infos, int *options);
int					ft_isnan(char **s, long double nb,
						t_nbinfos *infos, int *options);

wchar_t				unicode(wchar_t n, int bytes);
char				*getwcharac(va_list va, int *options);
char				*getwstr(va_list va, int *options);
int					bytesnb_in_acc(wchar_t *s, int acc);
void				write_wstr(char *s, wchar_t *arg, int acc);

int					bytesnb(wchar_t c);

int					max_dpow(double nb);
long double			ft_pow(long double nb, int pow);
long double			dround(long double d, int acc);
int					useless_zero_nb(long double nb, int acc, char type);
int					count_useless_zeros(long double nb, int acc);

char				*geto(va_list va, int *options);

double				abs2(double x);
double				max(double a, double b);
double				min(double a, double b);
double				is_neg(double x);

#endif
