/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_bigs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:44:36 by curquiza          #+#    #+#             */
/*   Updated: 2017/09/16 15:07:06 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_wchar_len(wchar_t *wchar_str)
{
	int		len;

	len = 0;
	while (*wchar_str)
	{
		len++;
		wchar_str++;
	}
	return (len);
}

static int	ft_check_precision(t_arg *current, int ret, int i)
{
	if (current->precision == 1 && current->preci_digit < i + ret)
	{
		ft_bzero(current->rslt + i, ret);
		return (-1);
	}
	return (0);
}

static int	ft_apply_conv(wchar_t *wchar_str, t_arg *current)
{
	int		i;
	int		ret;

	i = ft_wchar_len(wchar_str);
	current->rslt = ft_memalloc(sizeof(wchar_t) * i + 1);
	i = 0;
	while (*wchar_str)
	{
		if (current->precision == 1 && current->preci_digit == i)
			break ;
		if ((ret = ft_wchar_in_str(*wchar_str,
									(unsigned char *)current->rslt + i)) == -1)
		{
			ft_bzero(current->rslt, ft_strlen(current->rslt));
			current->conv_len = 0;
			return (-1);
		}
		if (ft_check_precision(current, ret, i) == -1)
			break ;
		i += ret;
		current->conv_len += ret;
		wchar_str++;
	}
	return (0);
}

int			ft_conv_bigs(va_list arg, t_arg *current)
{
	wchar_t		*s;

	s = va_arg(arg, wchar_t *);
	if (!s)
	{
		current->rslt = ft_strdup("(null)");
		current->conv_len = ft_strlen(current->rslt);
	}
	else if (s && ft_apply_conv(s, current) == -1)
	{
		current->wchar_err = 1;
		return (-1);
	}
	ft_apply_precision_conv_s(current);
	ft_apply_padding(current);
	return (0);
}
