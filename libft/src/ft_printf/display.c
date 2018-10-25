/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:54:57 by curquiza          #+#    #+#             */
/*   Updated: 2017/09/16 15:08:37 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_cpy_until_percent(char *dst, char *src)
{
	int		i;

	i = 0;
	while (src[i] && src[i] != '%')
	{
		dst[i] = src[i];
		i++;
	}
	return (i);
}

static int	ft_fill_final_str(char *s, t_data data, char *final)
{
	int		i;
	int		len;
	t_arg	*tmp;

	tmp = data.arg_lst;
	i = 0;
	while (*s)
	{
		if (tmp && tmp->wchar_err == 1)
		{
			ft_putstr(final);
			return (-1);
		}
		len = ft_cpy_until_percent(final + i, s);
		s += len;
		i += len;
		if (tmp)
		{
			ft_memmove(final + i, tmp->rslt, tmp->conv_len);
			s += tmp->format_len;
			i += tmp->conv_len;
			tmp = tmp->next;
		}
	}
	return (0);
}

static void	ft_del_all(t_data *data, char **s)
{
	t_arg	*supp;
	t_arg	*tmp;

	tmp = data->arg_lst;
	while (tmp)
	{
		supp = tmp;
		tmp = tmp->next;
		ft_strdel(&supp->rslt);
		free(supp);
		supp = NULL;
	}
	ft_strdel(s);
	ft_bzero(data, sizeof(*data));
}

int			ft_display_and_exit(char *s, t_data data)
{
	char	*final;
	int		final_len;

	final_len = ft_strlen(s) + data.conv_len - data.format_len;
	final = ft_strnew(final_len);
	if (ft_fill_final_str(s, data, final) == -1)
	{
		ft_del_all(&data, &final);
		return (-1);
	}
	write(1, final, final_len);
	ft_del_all(&data, &final);
	return (final_len);
}
