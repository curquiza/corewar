/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_bigc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:44:34 by curquiza          #+#    #+#             */
/*   Updated: 2017/09/16 15:07:01 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_fill_4bytes_wchar(wint_t c, unsigned char *s)
{
	s[0] = 0xf0 | ((c >> 18) & 0x07);
	s[1] = 0x80 | ((c >> 12) & 0x3F);
	s[2] = 0x80 | ((c >> 6) & 0x3F);
	s[3] = 0x80 | (c & 0x3F);
	return (4);
}

int		ft_fill_3bytes_wchar(wint_t c, unsigned char *s)
{
	s[0] = 0xe0 | ((c >> 12) & 0x0F);
	s[1] = 0x80 | ((c >> 6) & 0x3F);
	s[2] = 0x80 | (c & 0x3F);
	return (3);
}

int		ft_fill_2bytes_wchar(wint_t c, unsigned char *s)
{
	s[0] = 0xc0 | ((c >> 6) & 0x1F);
	s[1] = 0x80 | (c & 0x3F);
	return (2);
}

/*
** ft_wchar_in_str :
** Remplit la chaine de char s avec le caractère wint_t c.
** Retourne -1 si le caractère unicode n'est pas valide, la longueur de
** l'unicode sinon.
*/

int		ft_wchar_in_str(wint_t c, unsigned char *s)
{
	if (MB_CUR_MAX == 1)
	{
		if (c >= 0 && c <= 0xFF)
		{
			s[0] = (unsigned char)c;
			return (1);
		}
		return (-1);
	}
	if (c >= 0 && c <= 0x7F)
	{
		s[0] = (unsigned char)c;
		return (1);
	}
	else if (c >= 0x80 && c <= 0x7FF)
		return (ft_fill_2bytes_wchar(c, s));
	else if ((c >= 0x800 && c <= 0xD7FF) || (c >= 0xE000 && c <= 0xFFFF))
		return (ft_fill_3bytes_wchar(c, s));
	else if (c >= 0x10000 && c <= 0x10FFFF)
		return (ft_fill_4bytes_wchar(c, s));
	return (-1);
}

int		ft_conv_bigc(va_list arg, t_arg *current)
{
	int		ret;

	current->rslt = ft_memalloc(sizeof(wint_t));
	ret = ft_wchar_in_str(va_arg(arg, wint_t), (unsigned char *)current->rslt);
	if (ret != -1)
		current->conv_len = ret;
	else
	{
		current->wchar_err = 1;
		return (-1);
	}
	ft_apply_padding(current);
	return (0);
}
