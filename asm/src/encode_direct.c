/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_direct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 10:43:41 by sfranc            #+#    #+#             */
/*   Updated: 2019/02/14 10:43:43 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_ex_ret		get_direct_label(unsigned char *output, char *label,
	t_symbol *symbol_table, int offset)
{
	unsigned int	*tmp;
	t_symbol		*label_ptr;

	tmp = (unsigned int*)output;
	if ((label_ptr = search_symbol_table(symbol_table, label)) == NULL)
		return (label_not_found(label));
	*tmp = ft_swap_int((unsigned int)(label_ptr->offset - offset));
	return (SUCCESS);
}

static void			get_direct_value(unsigned char *output, char *value)
{
	unsigned int *tmp;

	tmp = (unsigned int*)output;
	*tmp = ft_swap_int((unsigned int)ft_atoi(value));
	return ;
}

t_ex_ret			get_direct(t_src_file *file, int i, int j, int pos)
{
	if (file->ast[i]->opcode->index)
		return (get_indirect(file, i, j, pos));
	if ((file->ast[i]->arg_type[j] & T_LAB) == T_LAB)
	{
		if (get_direct_label(file->output + pos, file->ast[i]->arguments[j],
			file->symbol_table, file->ast[i]->offset) == FAILURE)
		{
			return (FAILURE);
		}
	}
	else
		get_direct_value(file->output + pos, file->ast[i]->arguments[j]);
	return (SUCCESS);
}
