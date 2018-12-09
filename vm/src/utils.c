#include "vm.h"

void	exit_malloc_err(void)
{
	clean_all();
	ft_dprintf(2, "Malloc error\n");
	exit(FAILURE);
}

t_bool	flag_is_applied(int flag, t_vm *vm)
{
	return ((flag & vm->flag) == flag);
}

/*
** Handle vm circle memory
*/
int		get_mem_index(int index)
{
	return (index % (MEM_SIZE - 1));
}

/*/!\ ne vérifie pas si c'est un T_REG. Si je n'ajoute pas cette condition à la*/
/*function -> changer le nom en is_valid_reg_index*/
t_bool	is_valid_reg(int index)
{
	return (index > 0 && index <= REG_NUMBER);
}
