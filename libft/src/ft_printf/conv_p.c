/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 18:06:08 by curquiza          #+#    #+#             */
/*   Updated: 2017/09/16 15:07:26 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_conv_p(va_list arg, t_arg *current)
{
	char	*tmp;

	current->rslt = ft_unsnum_to_str(
				(unsigned long long int)va_arg(arg, void *), LITTLE_HEXA_BASE);
	current->conv_len = ft_strlen(current->rslt);
	tmp = current->rslt;
	current->rslt = ft_strnew(current->conv_len + 2);
	ft_memmove(current->rslt + 2, tmp, current->conv_len);
	current->rslt[0] = '0';
	current->rslt[1] = 'x';
	current->conv_len += 2;
	ft_strdel(&tmp);
	ft_apply_precision_num_conv(current);
	ft_apply_padding(current);
	return (0);
}
