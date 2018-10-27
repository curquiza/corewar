/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_u_bigu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 16:56:20 by curquiza          #+#    #+#             */
/*   Updated: 2017/09/16 15:07:45 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_apply_conv(va_list arg, t_arg *current)
{
	if (!ft_strcmp(current->modif, "l") || current->conv == 'U')
		return (ft_unsnum_to_str(va_arg(arg, unsigned long), DECI_BASE));
	if (!ft_strcmp(current->modif, "hh"))
		return (ft_unsnum_to_str((unsigned char)va_arg(arg, int), DECI_BASE));
	if (!ft_strcmp(current->modif, "h"))
		return (ft_unsnum_to_str((unsigned short)va_arg(arg, int), DECI_BASE));
	if (!ft_strcmp(current->modif, "ll"))
		return (ft_unsnum_to_str(va_arg(arg, unsigned long long), DECI_BASE));
	if (!ft_strcmp(current->modif, "j"))
		return (ft_unsnum_to_str(va_arg(arg, uintmax_t), DECI_BASE));
	if (!ft_strcmp(current->modif, "z"))
		return (ft_unsnum_to_str(va_arg(arg, size_t), DECI_BASE));
	else
		return (ft_unsnum_to_str((unsigned int)va_arg(arg, int), DECI_BASE));
}

int			ft_conv_u_bigu(va_list arg, t_arg *current)
{
	current->rslt = ft_apply_conv(arg, current);
	current->conv_len = ft_strlen(current->rslt);
	ft_apply_precision_num_conv(current);
	ft_apply_padding(current);
	return (0);
}
