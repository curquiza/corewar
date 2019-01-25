#include "asm.h"

t_symbol		*search_symbol_table(t_symbol *symbol_table, char *str)
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

static t_ex_ret 		get_indirect_label(unsigned char *output, char *label, t_symbol *symbol_table, int offset)
{
	unsigned short	*tmp;
	t_symbol		*label_ptr;

	tmp = (unsigned short*)output;
	if ((label_ptr = search_symbol_table(symbol_table, label)) == NULL)
		return (label_not_found(label));
	
	ft_printf("get_indirect_label:%s %d\n", label, (unsigned short)(offset - label_ptr->offset - offset)); // debug
	*tmp = ft_swap_short((unsigned short)(label_ptr->offset - offset));
	return (SUCCESS);
}

static void			get_indirect_value(unsigned char *output, char *value)
{
	unsigned short *tmp;

	tmp = (unsigned short*)output;
	ft_printf("get_indirect_value: %d\n", ft_atoi(value)); // debug
	*tmp = ft_swap_short((unsigned short)ft_atoi(value)); // swap ??
	return ;
}

t_ex_ret 		get_indirect(t_src_file *file, int i, int j, int pos)
{
	if ((file->ast[i]->arg_type[j] & T_LAB) == T_LAB)
	{
		if (get_indirect_label(file->output + pos, file->ast[i]->arguments[j], file->symbol_table, file->ast[i]->offset) == FAILURE)
			return (FAILURE);
	}
	else
		get_indirect_value(file->output + pos, file->ast[i]->arguments[j]);
	return (SUCCESS);
}