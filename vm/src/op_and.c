#include "vm.h"

/*
** Get 4 bytes
*/
static int	get_value_according_to_type(t_vm *vm, t_processus *proc, t_param *p)
{
	int		rslt;

	if (p->type == T_REG && is_valid_reg(p->value))
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

void	op_and(t_vm *vm, t_processus *proc, t_param *params)
{
	int		rslt;
	int		p1;
	int		p2;

	print_str("\tAND\n", ALL, vm);
	p1 = get_value_according_to_type(vm, proc, &params[0]);
	p2 = get_value_according_to_type(vm, proc, &params[1]);
	rslt = p1 & p2;
	ft_dprintf(vm->trace_fd, "p1 = 0x%x\n", p1);
	ft_dprintf(vm->trace_fd, "p2 = 0x%x\n", p2);
	ft_dprintf(vm->trace_fd, "rslt = 0x%x\n", rslt);
	if (rslt == 0)
		proc->carry = 1;
	/*if (params[2].value >= 0 && params[2].value < REG_NUMBER)*/
	if (is_valid_reg(params[2].value) == TRUE)
		proc->reg[params[2].value - 1] = rslt;
}
