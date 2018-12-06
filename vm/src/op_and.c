#include "vm.h"

void	op_and(t_vm *vm, t_processus *proc, t_param *params)
{
	int		rslt;

	print_str("\tAND\n", ALL, vm);
	rslt = (t_byte) params[0].value & (t_byte) params[1].value;
	if (rslt == 0)
		proc->carry = 1;
	if (params[2].value >= 0 && params[2].value < REG_NUMBER)
		proc->reg[params[2].value] = rslt;
}
