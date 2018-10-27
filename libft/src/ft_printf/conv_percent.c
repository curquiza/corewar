/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_percent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:44:55 by curquiza          #+#    #+#             */
/*   Updated: 2017/09/16 15:07:31 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_conv_percent(va_list arg, t_arg *current)
{
	(void)arg;
	current->rslt = ft_strdup("%");
	current->conv_len = 1;
	ft_apply_padding(current);
	return (0);
}
