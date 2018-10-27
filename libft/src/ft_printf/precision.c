/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:57:37 by curquiza          #+#    #+#             */
/*   Updated: 2017/09/16 15:09:09 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_begin_with_sign(char *s, t_arg *current)
{
	if (!ft_strncmp(s, "0x", 2) || !ft_strncmp(s, "0X", 2))
		return (2);
	if (*s == '+' || *s == '-' || *s == ' ')
		return (1);
	if ((current->conv == 'o' || current->conv == 'O')
		&& current->flag_sharp == 1
		&& ft_strcmp(current->rslt, "0"))
		return (1);
	return (0);
}

static void	ft_zero_precision_with_zero(int sign, t_arg *current)
{
	if ((current->conv == 'o' || current->conv == 'O')
		&& current->flag_sharp == 1)
		;
	else
	{
		current->rslt[sign] = '\0';
		current->conv_len--;
	}
}

void		ft_apply_precision_num_conv(t_arg *current)
{
	char	*tmp;
	int		sign;
	int		i;

	sign = ft_begin_with_sign(current->rslt, current);
	if (!ft_strcmp(current->rslt + sign, "0")
		&& current->precision == 1 && current->preci_digit == 0)
		ft_zero_precision_with_zero(sign, current);
	else if (current->precision == 1 && current->preci_digit > 0
		&& current->preci_digit > current->conv_len - sign)
	{
		tmp = current->rslt;
		current->rslt = ft_strnew(sign + current->preci_digit);
		ft_memmove(current->rslt, tmp, sign);
		i = current->preci_digit - (current->conv_len - sign);
		ft_memset(current->rslt + sign, '0', i);
		ft_memmove(current->rslt + sign + i, tmp + sign,
											current->conv_len - sign);
		ft_strdel(&tmp);
		current->conv_len = sign + current->preci_digit;
	}
}

void		ft_apply_precision_conv_s(t_arg *current)
{
	if (current->precision == 1 && current->conv_len > current->preci_digit)
	{
		ft_bzero(current->rslt + current->preci_digit,
					current->conv_len - current->preci_digit);
		current->conv_len = current->preci_digit;
	}
}
