#include "asm.h"

/*
** create a symbol table with labels and their offset.
*/

static t_ex_ret		new_symbol(t_symbol **new, char *name, int offset)
{
	if (!(*new = (t_symbol*)ft_memalloc(sizeof(t_symbol))))
		return (ft_ret_err(ERR_MALLOC));
	(*new)->label = name;
	(*new)->offset = offset;
	return (SUCCESS);
}

static void			add_symbol(t_symbol **symbols, t_symbol *new)
{
	t_symbol	*tmp;

	if (!*symbols)
	{
		*symbols = new;
		return ;
	}
	tmp = *symbols;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return ;
}

t_ex_ret			link_symbol(t_symbol **symbols, char *name, int offset)
{
	t_ex_ret			ret;
	t_symbol			*new;

	if ((ret = new_symbol(&new, name, offset)) == SUCCESS)
		add_symbol(symbols, new);
	return (ret);
}

void				free_symbol_table(t_symbol **symbols)
{
	t_symbol	*tmp;
	t_symbol	*prev;

	if (!*symbols)
		return ;
	tmp = *symbols;
	while (tmp)
	{
		prev = tmp;
		tmp = tmp->next;
		free(prev);
	}
	*symbols = NULL;
}

t_ex_ret			create_symbol_table(t_src_file *file)
{
	int i;

	i = 0;
	while (file->ast[i])
	{
		if (file->ast[i]->label)
			if (link_symbol(&file->symbol_table, file->ast[i]->label, file->ast[i]->offset) == FAILURE)
				return (FAILURE);
		i++;
	}
	return (SUCCESS);
}