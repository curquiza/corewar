#include "vm.h"

/*
** Fork : fork the current processus
** p1 = dir
** No OCP
*/

void	op_fork(t_vm *vm, t_processus *proc, t_param *params)
{
	unsigned short	new_addr;
	t_processus		*new_proc;
	
	new_addr = (unsigned short) (proc->pc + (params[0].value % IDX_MOD));
	new_proc = new_processus(get_mem_index(new_addr), vm);
	new_proc->live = proc->live;
	new_proc->carry = proc->carry;
	ft_memmove(new_proc->reg, proc->reg, REG_NUMBER * sizeof(*proc->reg));
	add_processus(&vm->proc, new_proc);
}
