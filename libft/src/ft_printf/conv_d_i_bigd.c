/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_d_i_bigd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 17:20:03 by curquiza          #+#    #+#             */
/*   Updated: 2017/09/16 15:07:16 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_apply_conv(va_list arg, t_arg *current)
{
	if (!ft_strcmp(current->modif, "l") || current->conv == 'D')
		return (ft_num_to_str(va_arg(arg, long), DECI_BASE));
	if (!ft_strcmp(current->modif, "hh"))
		return (ft_num_to_str((signed char)va_arg(arg, int), DECI_BASE));
	if (!ft_strcmp(current->modif, "h"))
		return (ft_num_to_str((short)va_arg(arg, int), DECI_BASE));
	if (!ft_strcmp(current->modif, "ll"))
		return (ft_num_to_str(va_arg(arg, long long), DECI_BASE));
	if (!ft_strcmp(current->modif, "j"))
		return (ft_num_to_str(va_arg(arg, intmax_t), DECI_BASE));
	if (!ft_strcmp(current->modif, "z"))
		return (ft_num_to_str(va_arg(arg, size_t), DECI_BASE));
	else
		return (ft_num_to_str(va_arg(arg, int), DECI_BASE));
}

int			ft_conv_d_i_bigd(va_list arg, t_arg *current)
{
	current->rslt = ft_apply_conv(arg, current);
	current->conv_len = ft_strlen(current->rslt);
	ft_apply_sign_flags(current);
	ft_apply_precision_num_conv(current);
	ft_apply_padding(current);
	return (0);
}
