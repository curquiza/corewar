#include "vm.h"

/*
** Lldi : Like ldi, but without any address restriction
** p1 = reg | dir | ind
** p2 = reg | dir
** p3 = reg
** Modify the carry.
*/

void	op_lldi(t_vm *vm, t_processus *proc, t_param *params)
{
	int		reg_index;
	int		v_to_ld;
	int		p1;
	int		p2;

	print_str("\tExecuting LLDI\n", ALL, vm);
	reg_index = params[2].value;
	p1 = get_value_according_to_type(vm, proc, &params[0], RESTRICT);
	p2 = get_value_according_to_type(vm, proc, &params[1], RESTRICT);
	v_to_ld = memvalue_to_uint32_norestrict(vm->memory, proc, p1 + p2, REG_SIZE);
	proc->reg[reg_index - 1] = v_to_ld;
	proc->carry = v_to_ld == 0 ? 1 : 0 ;
}
