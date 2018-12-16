#include "vm.h"

/*
** Sti : indirect store in memory. Stores p1 at (p2 + p3) address.
** p1 = reg
** p2 = reg | dir | ind
** p3 = reg | dir
*/

void	op_sti(t_vm *vm, t_processus *proc, t_param *params)
{
	int		p1;
	int		p2;
	int		p3;

	print_str("\tExecuting STI\n", ALL, vm);
	/*if (is_valid_reg_index(params[0].value) == TRUE)*/
	/*{*/
		p1 = proc->reg[params[0].value - 1];
		p2 = get_value_according_to_type(vm, proc, &params[1], RESTRICT);
		p3 = get_value_according_to_type(vm, proc, &params[2], RESTRICT);
		/*store_4bytes(vm, (unsigned short) (proc->pc + (p2 + p3)), p1, proc);*/
		store_4bytes(vm, p2 + p3, p1, proc);
	/*}*/
}
