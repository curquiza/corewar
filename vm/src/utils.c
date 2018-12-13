#include "vm.h"

void	exit_malloc_err(void)
{
	clean_all();
	ft_dprintf(2, "Malloc error\n");
	exit(FAILURE);
}

t_bool	flag_is_applied(int flag, t_vm *vm)
{
	return ((flag & vm->flag) == flag);
}

/*
** Handle vm circle memory
*/
int		get_mem_index(unsigned short index)
{
	return (index % (MEM_SIZE - 1));
}

t_bool	is_valid_reg_index(int index)
{
	return (index > 0 && index <= REG_NUMBER);
}

/*
** Get 4 bytes
*/
int	get_value_according_to_type(t_vm *vm, t_processus *proc, t_param *p)
{
	int		rslt;

	if (p->type == T_REG && is_valid_reg_index(p->value))
		return (proc->reg[p->value - 1]);
	if (p->type == T_IND)
	{
		rslt = memvalue_to_uint32(vm->memory, proc->pc + (p->value % IDX_MOD), REG_SIZE);
		return (rslt);
	}
	if (p->type == T_DIR)
		return (p->value);
	return (0);
}
