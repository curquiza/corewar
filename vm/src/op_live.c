#include "vm.h"

void	op_live(t_vm *vm, t_processus *proc)
{
	ft_printf("LIVE\n");
	ft_printf("Un processus dit que le joueur %d (%s) est en vie\n", 0, "titi");
	proc->live = TRUE;
	vm->lives += 1;
}
