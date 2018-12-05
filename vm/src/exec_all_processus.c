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

void		print_params(t_param *params, t_vm *vm)
{
	int		i;

	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		ft_dprintf(vm->trace_fd, "Params %d\n", i + 1);
		ft_dprintf(vm->trace_fd, " > type = %b\n", params[0].type);
		ft_dprintf(vm->trace_fd, " > size = %d\n", params[0].size);
		ft_dprintf(vm->trace_fd, " > value = 0x%x\n", params[0].value);
		i++;
	}
}

void		exec_all_proc(t_vm *vm)
{
	t_processus	*proc;
	t_param		params[MAX_ARGS_NUMBER];

	proc = vm->proc;
	while (proc)
	{
		if (proc->current_op == NULL)
			proc->current_op = get_op_from_proc(vm, proc);
		proc->cycles += 1;
		if (proc->cycles == proc->current_op->cycles && proc->current_op)
		{
			//parse params
			parse_op_params(vm, proc, params);
			print_params(params, vm); //DEBUG
			proc->current_op->func(vm, proc);
			proc->cycles = 0;
			proc->current_op = NULL;
			move_to_next_op(vm, proc);
		}
		proc = proc->next;
	}
}
