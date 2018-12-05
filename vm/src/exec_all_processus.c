#include "vm.h"

void		print_params(t_param *params, t_vm *vm)
{
	int		i;

	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		ft_dprintf(vm->trace_fd, "Params %d\n", i + 1);
		if (params[i].type == T_REG)
			ft_dprintf(vm->trace_fd, " > type = T_REG\n");
		else if (params[i].type == T_DIR)
			ft_dprintf(vm->trace_fd, " > type = T_DIR\n");
		else if (params[i].type == T_IND)
			ft_dprintf(vm->trace_fd, " > type = T_IND\n");
		else
			ft_dprintf(vm->trace_fd, " > type = UNKNOWN\n");
		ft_dprintf(vm->trace_fd, " > size = %d\n", params[i].size);
		ft_dprintf(vm->trace_fd, " > value = 0x%x\n", params[i].value);
		i++;
	}
}

static t_op	*get_op_from_proc(t_vm *vm, t_processus *proc)
{
	t_byte		opcode;

	opcode = vm->memory[proc->index].value;
	if (opcode <= 0 || opcode > OP_NUMBER)
		return (NULL);
	return (&g_op[opcode - 1]);
}

static void		move_to_next_op(t_vm *vm, t_processus *proc, t_param *params)
{
	int		i;

	vm->memory[proc->index].proc = FALSE;
	if (params && proc->current_op)
	{
		i = 0;
		while (i < proc->current_op->param_nb)
		{
			proc->index += params[i].size + 1;
			i++;
		}
		proc->index = get_mem_index(proc->index);
	}
	else
		proc->index = get_mem_index(proc->index + 1);
	vm->memory[proc->index].proc = TRUE;
	// move PC ?
}

static void		exec_one_cycle(t_vm *vm, t_processus *proc, t_param *params)
{
	proc->cycles += 1;
	if (proc->cycles == proc->current_op->cycles && proc->current_op)
	{
		parse_op_params(vm, proc, params);
		print_params(params, vm); //DEBUG
		proc->current_op->func(vm, proc);
		move_to_next_op(vm, proc, params);
		proc->current_op = NULL;
		proc->cycles = 0;
	}
}

void		exec_all_proc(t_vm *vm)
{
	t_processus	*proc;
	t_param		params[MAX_ARGS_NUMBER];

	proc = vm->proc;
	while (proc)
	{
		proc->current_op = get_op_from_proc(vm, proc);
		if (proc->current_op == NULL)
			move_to_next_op(vm, proc, NULL);
		else
			exec_one_cycle(vm, proc, params);
		proc = proc->next;
	}
}
