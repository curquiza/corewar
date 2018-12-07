#include "vm.h"

void	op_sti(t_vm *vm, t_processus *proc, t_param *params)
{
	(void)vm;
	(void)proc;
	(void)params;
	print_str("\tSTI\n", ALL, vm);
}
