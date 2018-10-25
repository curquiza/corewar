/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 15:11:15 by curquiza          #+#    #+#             */
/*   Updated: 2017/09/16 15:11:18 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

# include <stdarg.h>
# include <wchar.h>

# define LITTLE_HEXA_BASE "0123456789abcdef"
# define BIG_HEXA_BASE "0123456789ABCDEF"
# define DECI_BASE "0123456789"
# define OCTAL_BASE "01234567"
# define BIN_BASE "01"
# define CONV "bsSpdDioOuUxXcC%"
# define NUM_CONV "bpdDioOuUxX"

typedef	struct	s_arg
{
	char			*rslt;
	int				format_len;
	int				conv_len;
	int				flag_sharp;
	int				flag_zero;
	int				flag_minus;
	int				flag_plus;
	int				flag_blank;
	int				min_width;
	int				precision;
	int				preci_digit;
	char			modif[3];
	char			conv;
	int				wchar_err;
	struct s_arg	*next;
}				t_arg;

typedef struct	s_data
{
	int				format_len;
	int				conv_len;
	t_arg			*arg_lst;
}				t_data;

/*
** ft_printf.c
*/
int				ft_printf(char *s, ...);

/*
** Parsing
*/
t_arg			*ft_new_arglst(t_arg **alst);
int				ft_go_to_conv(char *s);
int				ft_is_flag(char c);
int				ft_is_modifier(char *s);
long long int	ft_str_to_ulli(const char *str);
int				ft_parsing(char *s, t_arg *current);

/*
** Signed flags (+' '#)
*/
void			ft_apply_sign_flags(t_arg *current);

/*
** Precision
*/
int				ft_begin_with_sign(char *s, t_arg *current);
void			ft_apply_precision_num_conv(t_arg *current);
void			ft_apply_precision_conv_s(t_arg *current);

/*
** Padding
*/
void			ft_apply_padding(t_arg *current);

/*
** Tools for conversions
*/

char			*ft_num_to_str(long long int n, char *tab_base);
char			*ft_unsnum_to_str(unsigned long long int n, char *tab_base);
int				ft_wchar_in_str(wint_t c, unsigned char *s);

/*
** Conversions
*/
int				ft_conv_x_bigx(va_list arg, t_arg *current);
int				ft_conv_u_bigu(va_list arg, t_arg *current);
int				ft_conv_d_i_bigd(va_list arg, t_arg *current);
int				ft_conv_o_bigo(va_list arg, t_arg *current);
int				ft_conv_p(va_list arg, t_arg *current);
int				ft_conv_c(va_list arg, t_arg *current);
int				ft_conv_s(va_list arg, t_arg *current);
int				ft_conv_bigc(va_list arg, t_arg *current);
int				ft_conv_bigs(va_list arg, t_arg *current);
int				ft_conv_percent(va_list arg, t_arg *current);
int				ft_conv_b(va_list arg, t_arg *current);

/*
** Display
*/
int				ft_display_and_exit(char *s, t_data data);

#endif
