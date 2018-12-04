#include "vm.h"

t_op	*get_op_from_proc(t_vm *vm, t_processus *proc)
{
	t_byte		opcode;

	opcode = vm->memory[proc->index].value;
	if (opcode <= 0 || opcode > OP_NUMBER)
		return (NULL);
	return (&g_op[opcode - 1]);
}

void		move_to_next_op(t_vm *vm, t_processus *proc)
{
	vm->memory[proc->index].proc = FALSE;
	// move -> change proc->index
	// vm->memory[proc->index].proc = TRUE;
}

void		exec_all_proc(t_vm *vm)
{
	t_processus	*proc;

	proc = vm->proc;
	while (proc)
	{
		if (proc->current_op == NULL)
			proc->current_op = get_op_from_proc(vm, proc);
		proc->cycles += 1;
		if (proc->cycles == proc->current_op->cycles && proc->current_op)
		{
			proc->current_op->func(vm, proc);
			proc->cycles = 0;
			proc->current_op = NULL;
			move_to_next_op(vm, proc);
		}
		proc = proc->next;
	}
}
