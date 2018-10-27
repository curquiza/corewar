/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sign_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:59:16 by curquiza          #+#    #+#             */
/*   Updated: 2017/09/16 15:09:15 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_add_front_sign(t_arg *current, char sign)
{
	char	*tmp;

	tmp = current->rslt;
	current->rslt = ft_strnew(current->conv_len + 1);
	ft_memmove(current->rslt + 1, tmp, current->conv_len);
	current->rslt[0] = sign;
	current->conv_len++;
	ft_strdel(&tmp);
}

static void	ft_apply_flag_plus(t_arg *current)
{
	if ((current->conv == 'd' || current->conv == 'i' || current->conv == 'D')
		&& current->rslt[0] != '-')
		ft_add_front_sign(current, '+');
}

static void	ft_apply_flag_blank(t_arg *current)
{
	if ((current->conv == 'd' || current->conv == 'i' || current->conv == 'D')
		&& current->rslt[0] != '-')
		ft_add_front_sign(current, ' ');
}

static void	ft_apply_flag_sharp(t_arg *current)
{
	char	*tmp;

	if (!ft_strcmp(current->rslt, "0"))
		return ;
	if (current->conv == 'o' || current->conv == 'O')
	{
		ft_add_front_sign(current, '0');
		if (current->precision == 1 && current->preci_digit > 0)
			current->preci_digit--;
	}
	else if (current->conv == 'x' || current->conv == 'X')
	{
		tmp = current->rslt;
		current->rslt = ft_strnew(current->conv_len + 1);
		ft_memmove(current->rslt + 2, tmp, current->conv_len);
		current->rslt[0] = '0';
		current->rslt[1] = current->conv;
		current->conv_len += 2;
		ft_strdel(&tmp);
	}
}

void		ft_apply_sign_flags(t_arg *current)
{
	if (current->flag_plus == 1)
		ft_apply_flag_plus(current);
	else if (current->flag_blank == 1)
		ft_apply_flag_blank(current);
	else if (current->flag_sharp == 1)
		ft_apply_flag_sharp(current);
}
