#include "vm.h"

static void	move_proc_to(t_vm *vm, t_processus *proc, int index)
{
	vm->memory[proc->pc].proc = FALSE;
	proc->pc = get_mem_index(index);
	vm->memory[proc->pc].proc = TRUE;
}

void	op_zjmp(t_vm *vm, t_processus *proc, t_param *params)
{
	print_str("\tExecuting ZJMP\n", ALL, vm);
	if (proc->carry == 1)
		move_proc_to(vm , proc, proc->pc + (params[0].value % IDX_MOD));
}
