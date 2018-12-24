#include "vm.h"

/*
** Ldi : load a value into a registre.
** p1 = reg | dir | ind
** p2 = reg | dir
** p3 = reg
** Modify the carry.
**
** Bug VM zaz : int32_t in IND condition (in get_value_according_to_type) should
** be int16_t
*/

static int	get_value_according_to_type_ldi(t_vm *vm, t_processus *proc, t_param *p)
{
	int		rslt;

	if (p->type == T_REG && is_valid_reg_index(p->value))
		return (proc->reg[p->value - 1]);
	if (p->type == T_IND)
	{
		rslt = memvalue_to_int32_restrict(vm->memory, proc, p->value, REG_SIZE);
		return ((int32_t) rslt);
	}
	if (p->type == T_DIR)
		return ((int16_t) p->value);
	return (0);
}

static int32_t	memvalue_to_int32_ldi(t_memcase *vm_mem, int32_t index, int size)
{
	int32_t		rslt;
	/*int			tmp;*/

	rslt = 0;
	if (size >= 1)
		rslt |= (t_byte) vm_mem[index % MEM_SIZE].value;
	if (size >= 2)
		rslt = (rslt << 8) | (t_byte) vm_mem[(index + 1) % MEM_SIZE].value;
	if (size >= 3)
		rslt = (rslt << 8) | (t_byte) vm_mem[(index + 2) % MEM_SIZE].value;
	if (size >= 4)
		rslt = (rslt << 8) | (t_byte) vm_mem[(index + 3) % MEM_SIZE].value;
	return (rslt);
}

void	op_ldi(t_vm *vm, t_processus *proc, t_param *params)
{
	int		reg_index;
	int		v_to_ld;
	int		p1;
	int		p2;

	print_str("\tExecuting LDI\n", ALL, vm);
	reg_index = params[2].value;
	p1 = get_value_according_to_type_ldi(vm, proc, &params[0]);
	p2 = get_value_according_to_type_ldi(vm, proc, &params[1]);
	v_to_ld = memvalue_to_int32_ldi(vm->memory, proc->pc + (((int32_t) (p1 + p2))% IDX_MOD), REG_SIZE);
	proc->reg[reg_index - 1] = v_to_ld;
}
