/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 16:28:41 by curquiza          #+#    #+#             */
/*   Updated: 2018/11/19 16:28:43 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_is_int(char *s)
{
	int			i;
	int			gap;
	long int	tmp;

	if (!s || ft_strlen(s) <= 0)
		return (0);
	gap = (s[0] == '-' || s[0] == '+') ? 1 : 0;
	while (s[gap] == '0')
		gap++;
	i = 0;
	while (s[i + gap])
	{
		if (!ft_isdigit(s[i + gap]))
			return (0);
		i++;
	}
	if (i > 10)
		return (0);
	if (i < 10)
		return (1);
	tmp = ft_atoli(s);
	if (tmp < INT_MIN || tmp > INT_MAX)
		return (0);
	return (1);
}
