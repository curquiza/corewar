#include "vm.h"

void		print_params(t_param *params, t_vm *vm)
{
	int		i;

	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		ft_dprintf(vm->trace_fd, "\tParams %d\n", i + 1);
		if (params[i].type == T_REG)
			ft_dprintf(vm->trace_fd, "\t> type = T_REG\n");
		else if (params[i].type == T_DIR)
			ft_dprintf(vm->trace_fd, "\t> type = T_DIR\n");
		else if (params[i].type == T_IND)
			ft_dprintf(vm->trace_fd, "\t> type = T_IND\n");
		else
			ft_dprintf(vm->trace_fd, "\t> type = UNKNOWN\n");
		ft_dprintf(vm->trace_fd, "\t> size = %d\n", params[i].size);
		ft_dprintf(vm->trace_fd, "\t> value = 0x%x\n", params[i].value);
		i++;
	}
}

static t_op	*get_op_from_proc(t_vm *vm, t_processus *proc)
{
	t_byte		opcode;

	opcode = vm->memory[proc->pc].value;
	if (opcode <= 0 || opcode > OP_NUMBER)
		return (NULL);
	return (&g_op[opcode - 1]);
}

/*static void		move_to_next_op(t_vm *vm, t_processus *proc, t_param *params)*/
static void		move_to_next_op(t_processus *proc, t_param *params)
{
	int		i;

	/*vm->memory[proc->pc].proc = FALSE;*/
	if (params && proc->current_op)
	{
		proc->pc += 1;
		i = 0;
		while (i < proc->current_op->param_nb)
		{
			proc->pc += params[i].size;
			i++;
		}
		if (proc->current_op->ocp == TRUE)
			proc->pc += 1;
		proc->pc = get_mem_index(proc, 0, DEF_ADDR);
	}
	else
		proc->pc = get_mem_index(proc, 1, DEF_ADDR);
	/*vm->memory[proc->pc].proc = TRUE;*/
	/*proc->current_op = NULL;*/
	/*proc->cycles = 0;*/
}

static t_bool	need_move(t_processus *proc)
{
	if (proc->current_op->opcode == 0x09 && proc->carry == 1)
		return (FALSE);
	return (TRUE);
}

static void		exec_one_cycle(t_vm *vm, t_processus *proc, t_param *params)
{
	proc->cycles += 1;
	if (proc->cycles == proc->current_op->cycles && proc->current_op)
	{
		print_str2("\tNombre of cycles reaches for operation",
					proc->current_op->name,  ALL, vm);
		if (parse_op_params(vm, proc, params) == TRUE)
		{
			/*print_params(params, vm); //DEBUG*/
			proc->current_op->func(vm, proc, params);
		}
		else
			print_str2("\tNo op execution : error in OCP for operation",
						proc->current_op->name,  ALL, vm);
		print_str("\tMoving to the next operation\n", ALL, vm);
		if (need_move(proc) == TRUE)
			move_to_next_op(proc, params);
		proc->current_op = NULL;
		proc->cycles = 0;
	}
}

void		exec_all_proc(t_vm *vm)
{
	t_processus	*proc;
	t_param		params[MAX_ARGS_NUMBER];
	int			i;

	i = 1;
	proc = vm->proc;
	while (proc)
	{
		print_str_int("Exec processus", i, ALL, vm);
		print_str_int("\tPC =", proc->pc, ALL, vm);
		if (proc->current_op == NULL && get_op_from_proc(vm, proc) == NULL)
		{
			print_str("\tOpe unknown. Gonna move to the next case\n", ALL, vm);
			move_to_next_op(proc, NULL);
		}
		else if (proc->current_op == NULL && get_op_from_proc(vm, proc))
		{
			proc->current_op = get_op_from_proc(vm, proc);
			print_str2("\tExec one cycle of operation", proc->current_op->name,  ALL, vm);
			exec_one_cycle(vm, proc, params);
		}
		else
		{
			print_str2("\tExec one cycle of operation", proc->current_op->name,  ALL, vm);
			exec_one_cycle(vm, proc, params);
		}
		proc = proc->next;
		i++;
	}
}

/*void		exec_all_proc(t_vm *vm)*/
/*{*/
	/*t_processus	*proc;*/
	/*t_param		params[MAX_ARGS_NUMBER];*/
	/*int			i;*/

	/*i = 1;*/
	/*proc = vm->proc;*/
	/*while (proc)*/
	/*{*/
		/*print_str_int("Exec processus", i, ALL, vm);*/
		/*print_str_int("\tPC =", proc->pc, ALL, vm);*/
		/*proc->current_op = get_op_from_proc(vm, proc);*/
		/*if (proc->current_op == NULL)*/
		/*{*/
			/*print_str("\tOpe unknown. Gonna move to the next case\n", ALL, vm);*/
			/*move_to_next_op(vm, proc, NULL);*/
		/*}*/
		/*else*/
		/*{*/
			/*print_str2("\tExec one cycle of operation", proc->current_op->name,  ALL, vm);*/
			/*exec_one_cycle(vm, proc, params);*/
		/*}*/
		/*proc = proc->next;*/
		/*i++;*/
	/*}*/
/*}*/

