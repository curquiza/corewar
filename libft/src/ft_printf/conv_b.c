/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:44:17 by curquiza          #+#    #+#             */
/*   Updated: 2017/09/16 15:04:26 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_apply_conv(va_list arg, t_arg *current)
{
	if (!ft_strcmp(current->modif, "hh"))
		return (ft_unsnum_to_str((unsigned char)va_arg(arg, int), BIN_BASE));
	if (!ft_strcmp(current->modif, "h"))
		return (ft_unsnum_to_str((unsigned short)va_arg(arg, int), BIN_BASE));
	if (!ft_strcmp(current->modif, "l"))
		return (ft_unsnum_to_str(va_arg(arg, unsigned long), BIN_BASE));
	if (!ft_strcmp(current->modif, "ll"))
		return (ft_unsnum_to_str(va_arg(arg, unsigned long long), BIN_BASE));
	if (!ft_strcmp(current->modif, "j"))
		return (ft_unsnum_to_str(va_arg(arg, uintmax_t), BIN_BASE));
	if (!ft_strcmp(current->modif, "z"))
		return (ft_unsnum_to_str(va_arg(arg, size_t), BIN_BASE));
	else
		return (ft_unsnum_to_str((unsigned int)va_arg(arg, int), BIN_BASE));
}

static void	ft_complete_with_zero(t_arg *current, int len)
{
	char	*tmp;
	int		nbr_zero;

	tmp = current->rslt;
	current->conv_len = (len / 8 + 1) * 8;
	current->rslt = ft_strnew(current->conv_len);
	nbr_zero = 8 - len % 8;
	ft_memset(current->rslt, '0', nbr_zero);
	ft_memmove(current->rslt + nbr_zero, tmp, len);
	ft_strdel(&tmp);
}

static void	ft_binary_format(t_arg *current)
{
	char	*tmp;
	int		i;
	int		space;

	if (current->conv_len % 8 != 0)
		ft_complete_with_zero(current, current->conv_len);
	tmp = current->rslt;
	current->rslt = ft_strnew(current->conv_len + current->conv_len / 4 - 1);
	ft_memmove(current->rslt, tmp, 4);
	space = 0;
	i = 4;
	while (tmp[i])
	{
		current->rslt[i + space] = ' ';
		space++;
		ft_memmove(current->rslt + i + space, tmp + i, 4);
		i += 4;
	}
	current->conv_len += space;
	ft_strdel(&tmp);
}

int			ft_conv_b(va_list arg, t_arg *current)
{
	current->rslt = ft_apply_conv(arg, current);
	current->conv_len = ft_strlen(current->rslt);
	ft_binary_format(current);
	ft_apply_padding(current);
	return (0);
}
