/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:37:45 by curquiza          #+#    #+#             */
/*   Updated: 2017/09/16 15:09:00 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_get_flags(char *s, t_arg *current)
{
	int		len;

	len = 0;
	while (s[len] && ft_is_flag(s[len]) == 1)
	{
		if (s[len] == '#')
			current->flag_sharp = 1;
		else if (s[len] == '0')
			current->flag_zero = 1;
		else if (s[len] == '+')
			current->flag_plus = 1;
		else if (s[len] == '-')
			current->flag_minus = 1;
		else if (s[len] == ' ')
			current->flag_blank = 1;
		len++;
	}
	if (current->flag_plus == 1)
		current->flag_blank = 0;
	if (current->flag_minus == 1)
		current->flag_zero = 0;
	return (len);
}

static int	ft_get_min_width(char *s, t_arg *current)
{
	int		len;
	char	*nbr;

	len = 0;
	while (s[len] && ft_isdigit(s[len]) == 1)
		len++;
	if (len > 0)
	{
		nbr = ft_strsub(s, 0, len);
		current->min_width = (int)ft_str_to_ulli(nbr);
		if (current->min_width < 0)
			current->min_width = 0;
		ft_strdel(&nbr);
	}
	return (len);
}

static int	ft_get_modifiers(char *s, t_arg *current)
{
	int		len;
	int		ret;

	len = 0;
	ft_bzero(current->modif, 3);
	while (s[len] && (ret = ft_is_modifier(s + len)) != 0)
	{
		if (current->modif[0])
		{
			ft_putendl(current->modif);
			return (-1);
		}
		ft_strncpy(current->modif, s + len, ret);
		len += ret;
	}
	return (len);
}

static int	ft_get_precision(char *s, t_arg *current)
{
	int		len;
	char	*nbr;

	len = 0;
	if (s[len] != '.')
		return (len);
	current->precision = 1;
	len++;
	while (s[len] && ft_isdigit(s[len]) == 1)
		len++;
	if (len > 1)
	{
		nbr = ft_strsub(s + 1, 0, len - 1);
		current->preci_digit = (int)ft_str_to_ulli(nbr);
		if (current->preci_digit < 0)
			current->preci_digit = 0;
		ft_strdel(&nbr);
	}
	return (len);
}

/*
** ft_parsing :
** Récupère flags, largeur minimum, précision, modifieurs et conversion.
** Retourne -1 si ambiguité de modifiers ou abscence de conversion, sinon 0.
** NB : le pointeur *i est là uniquement pour faciliter la lecture du code.
*/

int			ft_parsing(char *s, t_arg *current)
{
	int		ret;
	int		*i;

	ret = 0;
	i = &current->format_len;
	current->format_len++;
	current->format_len += ft_get_flags(s + *i, current);
	current->format_len += ft_get_min_width(s + *i, current);
	current->format_len += ft_get_precision(s + *i, current);
	if ((ret = ft_get_modifiers(s + *i, current)) == -1)
		current->format_len += ft_go_to_conv(s);
	else
		current->format_len += ret;
	if (!s[*i] || !ft_strchr(CONV, s[*i]))
		return (-1);
	current->conv = s[*i];
	if (ft_strchr(NUM_CONV, current->conv) && current->precision == 1)
		current->flag_zero = 0;
	current->format_len++;
	if (ret == -1)
		return (-1);
	return (0);
}
