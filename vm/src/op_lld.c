#include "vm.h"

/*
** Lld : like ld but without any address restriction
** p1 = dir | ind
** p2 = reg
** Modify the carry.
*/

void	op_lld(t_vm *vm, t_processus *proc, t_param *params)
{
	int		reg_index;
	int		v_to_ld;

	print_str("\tExecuting LLD\n", ALL, vm);
	reg_index = params[1].value;
	v_to_ld = get_value_according_to_type(vm, proc, &params[0], DEF_ADDR);
	proc->reg[reg_index - 1] = v_to_ld;
	proc->carry = v_to_ld == 0 ? 1 : 0 ;
}
