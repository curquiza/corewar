#include "vm.h"

/*
** Ldi : load a value into a registre.
** p1 = reg | dir | ind
** p2 = reg | dir
** p3 = reg
** Modify the carry.
*/

void	op_ldi(t_vm *vm, t_processus *proc, t_param *params)
{
	int		reg_index;
	int		v_to_ld;
	int		p1;
	int		p2;

	print_str("\tExecuting LDI\n", ALL, vm);
	reg_index = params[2].value;
	/*if (is_valid_reg_index(reg_index))*/
	/*{*/
		p1 = get_value_according_to_type(vm, proc, &params[0], RESTRICT);
		p2 = get_value_according_to_type(vm, proc, &params[1], RESTRICT);
		/*v_to_ld = get_value_according_to_type(vm, proc, &params[0]);*/
		v_to_ld = memvalue_to_int32_restrict(vm->memory, proc, p1 + p2,
												REG_SIZE);
		proc->reg[reg_index - 1] = v_to_ld;
		proc->carry = v_to_ld == 0 ? 1 : 0 ;
	/*}*/
}
