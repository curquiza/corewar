/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 10:47:45 by sfranc            #+#    #+#             */
/*   Updated: 2019/02/14 10:47:51 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool		is_label_string(char *str)
{
	while (*str)
	{
		if (is_label_char(*str) == FALSE)
			return (FALSE);
		str++;
	}
	return (TRUE);
}

int			is_opcode(char *str)
{
	int		i;

	i = 0;
	while (i < NB_OPCODE)
	{
		if ((ft_strcmp(g_op_tab[i].name, str)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

t_bool		is_registre(char *str)
{
	if (*str == 'r' && ft_is_int(str + 1) \
			&& (ft_atoi(str + 1) >= 1) \
			&& (ft_atoi(str + 1) <= REG_NUMBER))
	{
		return (TRUE);
	}
	return (FALSE);
}

t_type		which_special_char(char c)
{
	if (c == DIRECT_CHAR)
		return (DIRECT);
	if (c == LABEL_CHAR)
		return (COLON);
	if (c == SEPARATOR_CHAR)
		return (SEPARATOR);
	return (NONE);
}
