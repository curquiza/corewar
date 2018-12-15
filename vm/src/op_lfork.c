#include "vm.h"

/*
** Lfork : fork the current processus with no address restriction
** p1 = dir
** No OCP
*/

void	op_lfork(t_vm *vm, t_processus *proc, t_param *params)
{
	t_processus		*new_proc;
	
	new_proc = new_processus(get_mem_index(proc, params[0].value, DEF_ADDR), vm);
	new_proc->live = proc->live;
	new_proc->carry = proc->carry;
	ft_memmove(new_proc->reg, proc->reg, REG_NUMBER * sizeof(*proc->reg));
	add_processus(&vm->proc, new_proc);
}
