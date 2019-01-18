#include "asm.h"

void		print_symbol_table(t_symbol *symbols)
{
	t_symbol *tmp;

	tmp = symbols;
	while (tmp)
	{
		ft_printf("%s\t%d\n", tmp->label, tmp->offset);
		tmp = tmp->next;
	}
}
