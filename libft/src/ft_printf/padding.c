/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:56:38 by curquiza          #+#    #+#             */
/*   Updated: 2017/09/16 15:08:56 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_apply_flag_minus(t_arg *current, char *tmp)
{
	int		i;

	i = current->min_width - current->conv_len;
	ft_memmove(current->rslt, tmp, current->conv_len);
	ft_memset(current->rslt + current->conv_len, ' ', i);
}

static void	ft_apply_flag_zero(t_arg *current, char *tmp)
{
	int		i;
	int		sign;

	if (ft_strchr(NUM_CONV, current->conv)
		&& (sign = ft_begin_with_sign(tmp, current)) != 0)
	{
		ft_memmove(current->rslt, tmp, sign);
		i = current->min_width - current->conv_len;
		ft_memset(current->rslt + sign, '0', i);
		ft_memmove(current->rslt + sign + i, tmp + sign,
												current->conv_len - sign);
	}
	else
	{
		i = current->min_width - current->conv_len;
		ft_memset(current->rslt, '0', i);
		ft_memmove(current->rslt + i, tmp, current->conv_len);
	}
}

static void	ft_basic_padding(t_arg *current, char *tmp)
{
	int		i;

	i = current->min_width - current->conv_len;
	ft_memset(current->rslt, ' ', i);
	ft_memmove(current->rslt + i, tmp, current->conv_len);
}

void		ft_apply_padding(t_arg *current)
{
	char	*tmp;

	if (current->min_width > current->conv_len)
	{
		tmp = current->rslt;
		current->rslt = ft_strnew(current->min_width);
		if (current->flag_minus)
			ft_apply_flag_minus(current, tmp);
		else if (current->flag_zero)
			ft_apply_flag_zero(current, tmp);
		else
			ft_basic_padding(current, tmp);
		current->conv_len = current->min_width;
		ft_strdel(&tmp);
	}
}
