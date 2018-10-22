/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 12:02:58 by curquiza          #+#    #+#             */
/*   Updated: 2017/09/16 15:08:49 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_numlen(long long int n, int base)
{
	int		size;

	size = 0;
	if (base < 2 || base > 16)
		return (0);
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / base;
		size++;
	}
	return (size);
}

char		*ft_num_to_str(long long int n, char *tab_base)
{
	int		base;
	char	*str;
	int		i;

	base = ft_strlen(tab_base);
	i = ft_numlen(n, base);
	if (base == 10 && n < 0)
		i++;
	str = ft_strnew(i--);
	str[0] = '0';
	if (base == 10 && n < 0)
		str[0] = '-';
	while (n != 0)
	{
		if (n < 0)
			str[i] = tab_base[-1 * (n % base)];
		else
			str[i] = tab_base[n % base];
		n /= base;
		i--;
	}
	return (str);
}

static int	ft_unsnumlen(unsigned long long int n, int base)
{
	int		size;

	size = 0;
	if (base < 2 || base > 16)
		return (0);
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / base;
		size++;
	}
	return (size);
}

char		*ft_unsnum_to_str(unsigned long long int n, char *tab_base)
{
	int		base;
	char	*str;
	int		i;

	base = ft_strlen(tab_base);
	i = ft_unsnumlen(n, base);
	str = ft_strnew(i--);
	str[0] = '0';
	while (n != 0)
	{
		str[i] = tab_base[n % base];
		n /= base;
		i--;
	}
	return (str);
}
