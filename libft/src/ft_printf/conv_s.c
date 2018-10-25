/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:48:15 by curquiza          #+#    #+#             */
/*   Updated: 2017/09/16 15:07:36 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_conv_s(va_list arg, t_arg *current)
{
	char	*s;

	if (!ft_strcmp(current->modif, "l"))
		return (ft_conv_bigs(arg, current));
	s = va_arg(arg, char *);
	if (s)
		current->rslt = ft_strdup(s);
	else
		current->rslt = ft_strdup("(null)");
	current->conv_len = ft_strlen(current->rslt);
	ft_apply_precision_conv_s(current);
	ft_apply_padding(current);
	return (0);
}
