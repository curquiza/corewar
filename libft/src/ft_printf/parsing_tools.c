/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:31:34 by curquiza          #+#    #+#             */
/*   Updated: 2017/09/16 15:09:05 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_go_to_conv(char *s)
{
	int		len;

	len = 0;
	while (s[len] && ft_is_modifier(s + len) != 0)
		len++;
	return (len);
}

int				ft_is_flag(char c)
{
	if (c == '#' || c == '0' || c == '+' || c == '-' || c == ' ')
		return (1);
	return (0);
}

int				ft_is_modifier(char *s)
{
	if (!ft_strncmp(s, "ll", 2) || !ft_strncmp(s, "hh", 2))
		return (2);
	if (*s == 'h' || *s == 'l' || *s == 'j' || *s == 'z')
		return (1);
	return (0);
}

long long int	ft_str_to_ulli(const char *str)
{
	unsigned long long int		result;

	if (!str)
		return (0);
	result = 0;
	while (*str && *str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result);
}
