#include "vm.h"

static int	get_value_according_to_type(t_vm *vm, t_processus *proc, t_param *p)
{
	if (p->type == T_REG && is_valid_reg(p->value))
		return (proc->reg[p->value]);
	if (p->type == T_IND)
		/*faux car ne prend qu'un seul byte a la place de 4 et car mauvaise adresse*/
		return (vm->memory[get_mem_index(proc->index + proc->pc)].value);
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
	/* /!\ Que fait la VM de zaz si invalide reg*/
	p1 = get_value_according_to_type(vm, proc, &params[0]);
	p2 = get_value_according_to_type(vm, proc, &params[1]);
	rslt = p1 & p2;
	if (rslt == 0)
		proc->carry = 1;
	if (params[2].value >= 0 && params[2].value < REG_NUMBER)
		proc->reg[params[2].value] = rslt;
}
