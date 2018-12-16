#include "vm.h"

/*
** Sub : p1 - p2 and put the result in registre p3
** p1 = reg
** p2 = reg
** p3 = reg
** Modify the carry
*/

void	op_sub(t_vm *vm, t_processus *proc, t_param *params)
{
	int		p1;
	int		p2;
	int		p3;

	print_str("\tExecuting SUB\n", ALL, vm);
	p1 = get_value_according_to_type(vm, proc, &params[0], RESTRICT);
	p2 = get_value_according_to_type(vm, proc, &params[1], RESTRICT);
	p3 = params[2].value;
	proc->reg[p3 - 1] = p1 - p2;
	proc->carry = ((p1 - p2) == 0) ? 1 : 0; // pas sûr pour le zero !
	/*ft_dprintf(vm->trace_fd, "p1 = 0x%x\n", p1); //DEBUG*/
	/*ft_dprintf(vm->trace_fd, "p2 = 0x%x\n", p2); //DEBUG*/
	/*ft_dprintf(vm->trace_fd, "p3 = 0x%x\n", p3); //DEBUG*/
}
