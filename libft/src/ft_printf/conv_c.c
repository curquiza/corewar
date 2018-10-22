/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:44:48 by curquiza          #+#    #+#             */
/*   Updated: 2017/09/16 15:07:11 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_conv_c(va_list arg, t_arg *current)
{
	if (!ft_strcmp(current->modif, "l"))
		return (ft_conv_bigc(arg, current));
	current->rslt = ft_memalloc(1);
	current->rslt[0] = (unsigned char)va_arg(arg, int);
	current->conv_len = 1;
	ft_apply_padding(current);
	return (0);
}
