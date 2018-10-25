/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:55:09 by curquiza          #+#    #+#             */
/*   Updated: 2017/09/16 15:08:44 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_go_next_percent(char **s)
{
	while (**s && **s != '%')
		(*s)++;
	if (!(**s))
		return (-1);
	return (0);
}

static void		ft_printf_loop(char *s, va_list arg, t_data *data,
										int (**f)(va_list, t_arg *))
{
	t_arg		*current_arg;
	int			ret_parsing;

	while (*s)
	{
		if (ft_go_next_percent(&s) == -1)
			break ;
		current_arg = ft_new_arglst(&data->arg_lst);
		ret_parsing = ft_parsing(s, current_arg);
		data->format_len += current_arg->format_len;
		if (ret_parsing != -1)
		{
			if (f[(int)current_arg->conv](arg, current_arg) == -1)
				break ;
		}
		data->conv_len += current_arg->conv_len;
		s += current_arg->format_len;
	}
}

static void		ft_init_ftab(int (**f)(va_list, t_arg *))
{
	f['c'] = &ft_conv_c;
	f['C'] = &ft_conv_bigc;
	f['s'] = &ft_conv_s;
	f['S'] = &ft_conv_bigs;
	f['i'] = &ft_conv_d_i_bigd;
	f['d'] = &ft_conv_d_i_bigd;
	f['D'] = &ft_conv_d_i_bigd;
	f['o'] = &ft_conv_o_bigo;
	f['O'] = &ft_conv_o_bigo;
	f['u'] = &ft_conv_u_bigu;
	f['U'] = &ft_conv_u_bigu;
	f['x'] = &ft_conv_x_bigx;
	f['X'] = &ft_conv_x_bigx;
	f['p'] = &ft_conv_p;
	f['%'] = &ft_conv_percent;
	f['b'] = &ft_conv_b;
}

int				ft_printf(char *s, ...)
{
	va_list		arg;
	t_data		data;
	int			(*f[122])(va_list, t_arg *);

	ft_bzero(&data, sizeof(data));
	ft_init_ftab(f);
	va_start(arg, s);
	ft_printf_loop(s, arg, &data, f);
	va_end(arg);
	return (ft_display_and_exit(s, data));
}
