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
