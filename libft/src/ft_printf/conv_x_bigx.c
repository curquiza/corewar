/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_x_bigx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 17:20:14 by curquiza          #+#    #+#             */
/*   Updated: 2017/09/16 15:14:46 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_apply_conv(va_list arg, t_arg *current)
{
	char	base[17];

	ft_bzero(base, 17);
	if (current->conv == 'x')
		ft_strncpy(base, LITTLE_HEXA_BASE, 16);
	else
		ft_strncpy(base, BIG_HEXA_BASE, 16);
	if (!ft_strcmp(current->modif, "l"))
		return (ft_unsnum_to_str(va_arg(arg, unsigned long), base));
	if (!ft_strcmp(current->modif, "hh"))
		return (ft_unsnum_to_str((unsigned char)va_arg(arg, int), base));
	if (!ft_strcmp(current->modif, "h"))
		return (ft_unsnum_to_str((unsigned short)va_arg(arg, int), base));
	if (!ft_strcmp(current->modif, "ll"))
		return (ft_unsnum_to_str(va_arg(arg, unsigned long long), base));
	if (!ft_strcmp(current->modif, "j"))
		return (ft_unsnum_to_str(va_arg(arg, uintmax_t), base));
	if (!ft_strcmp(current->modif, "z"))
		return (ft_unsnum_to_str(va_arg(arg, size_t), base));
	else
		return (ft_unsnum_to_str((unsigned int)va_arg(arg, int), base));
}

int			ft_conv_x_bigx(va_list arg, t_arg *current)
{
	current->rslt = ft_apply_conv(arg, current);
	current->conv_len = ft_strlen(current->rslt);
	ft_apply_sign_flags(current);
	ft_apply_precision_num_conv(current);
	ft_apply_padding(current);
	return (0);
}
