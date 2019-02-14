/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_indirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 10:43:43 by sfranc            #+#    #+#             */
/*   Updated: 2019/02/14 13:44:10 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_symbol			*search_symbol_table(t_symbol *symbol_table, char *str)
{
	t_symbol *tmp;

	tmp = symbol_table;
	while (tmp)
	{
		if (ft_strcmp(tmp->label, str) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static t_ex_ret		get_indirect_label(unsigned char *output,
						char *label, t_symbol *symbol_table, int offset)
{
	unsigned short	*tmp;
	t_symbol		*label_ptr;

	tmp = (unsigned short*)output;
	if ((label_ptr = search_symbol_table(symbol_table, label)) == NULL)
		return (label_not_found(label));
	*tmp = ft_swap_short((unsigned short)(label_ptr->offset - offset));
	return (SUCCESS);
}

static void			get_indirect_value(unsigned char *output, char *value)
{
	unsigned short *tmp;

	tmp = (unsigned short*)output;
	*tmp = ft_swap_short((unsigned short)ft_atoi(value));
	return ;
}

t_ex_ret			get_indirect(t_src_file *file, int i, int j, int pos)
{
	if ((file->ast[i]->arg_type[j] & T_LAB) == T_LAB)
	{
		if (get_indirect_label(file->output + pos, file->ast[i]->arguments[j],
			file->symbol_table, file->ast[i]->offset) == FAILURE)
		{
			return (FAILURE);
		}
	}
	else
		get_indirect_value(file->output + pos, file->ast[i]->arguments[j]);
	return (SUCCESS);
}
