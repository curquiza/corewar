#include "vm.h"

/*
** St : stores the value of the first parameter into the second one
** p1 = reg
** p2 = reg | ind
*/

void	op_st(t_vm *vm, t_processus *proc, t_param *params)
{
	int		v_to_st;

	print_str("\tExecuting ST\n", ALL, vm);
	if (is_valid_reg_index(params[0].value))
	{
		/*v_to_st = proc->reg[params[0].value - 1];*/
		v_to_st = 0xaabbccdd;
		if (params[1].type == T_REG && is_valid_reg_index(params[1].value))
			proc->reg[params[1].value - 1] = v_to_st;
		else if (params[1].type == T_IND)
		{
			store_4bytes(vm,
					/*(unsigned short) (proc->pc + ((params[1].value) % IDX_MOD)),*/
					(unsigned short) (proc->pc + (params[1].value)),
					v_to_st, proc);
			ft_dprintf(vm->trace_fd, "v_to_st = %d\n", v_to_st);
			ft_dprintf(vm->trace_fd, "addr = %d\n", (unsigned short) (proc->pc + (params[1].value)));
			ft_dprintf(vm->trace_fd, "get_mem_index(addr) = %d\n", get_mem_index((unsigned short) (proc->pc + (params[1].value))));
		}
	}
}
