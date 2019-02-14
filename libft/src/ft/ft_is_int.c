/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 16:28:41 by curquiza          #+#    #+#             */
/*   Updated: 2018/11/21 14:28:32 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_is_int(char *s)
{
	int			i;
	int			gap;
	long int	tmp;

	if (!s || ft_strlen(s) <= 0)
		return (FALSE);
	gap = (s[0] == '-' || s[0] == '+') ? 1 : 0;
	while (s[gap] == '0')
		gap++;
	i = 0;
	while (s[i + gap])
	{
		if (!ft_isdigit(s[i + gap]))
			return (FALSE);
		i++;
	}
	if (i > 10)
		return (FALSE);
	if (i < 10)
		return (TRUE);
	tmp = ft_atoli(s);
	if (tmp < INT_MIN || tmp > INT_MAX)
		return (FALSE);
	return (TRUE);
}
