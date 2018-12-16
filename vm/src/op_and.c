#include "vm.h"

/*
** And : p1 & p2 and put the result in registre p3
** p1 = reg | dir | ind
** p2 = reg | dir | ind
** p3 = reg
** Modify the carry
*/

void	op_and(t_vm *vm, t_processus *proc, t_param *params)
{
	int		p1;
	int		p2;

	print_str("\tExecuting AND\n", ALL, vm);
	/*if (is_valid_reg_index(params[2].value) == TRUE)*/
	/*{*/
		p1 = get_value_according_to_type(vm, proc, &params[0], RESTRICT);
		p2 = get_value_according_to_type(vm, proc, &params[1], RESTRICT);
		proc->reg[params[2].value - 1] = p1 & p2;
		proc->carry = ((p1 & p2) == 0) ? 1 : 0; // pas sûr pour le zero !
		ft_dprintf(vm->trace_fd, "p1 = 0x%x\n", p1); //DEBUG
		ft_dprintf(vm->trace_fd, "p2 = 0x%x\n", p2); //DEBUG
		ft_dprintf(vm->trace_fd, "p3 = 0x%x\n", params[2].value); //DEBUG
	/*}*/
}
