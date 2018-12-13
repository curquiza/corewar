#include "vm.h"

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

void	store_4bytes(t_vm *vm, unsigned short index, int value,
							t_processus *proc)
{
	t_memcase	op_case;

	op_case = vm->memory[proc->pc];

	vm->memory[get_mem_index(index)].value = (t_byte) ((value >> 24) & 0xff);
	ft_strcpy(vm->memory[get_mem_index(index)].color, op_case.color);
	vm->memory[get_mem_index(index)].color_visu = op_case.color_visu;

	vm->memory[get_mem_index(index + 1)].value = (t_byte) ((value >> 16) & 0xff);
	ft_strcpy(vm->memory[get_mem_index(index + 1)].color, op_case.color);
	vm->memory[get_mem_index(index + 1)].color_visu = op_case.color_visu;

	vm->memory[get_mem_index(index + 2)].value = (t_byte) ((value >> 8) & 0xff);
	ft_strcpy(vm->memory[get_mem_index(index + 2)].color, op_case.color);
	vm->memory[get_mem_index(index + 2)].color_visu = op_case.color_visu;

	vm->memory[get_mem_index(index + 3)].value = (t_byte) (value & 0xff);
	ft_strcpy(vm->memory[get_mem_index(index + 3)].color, op_case.color);
	vm->memory[get_mem_index(index + 3)].color_visu = op_case.color_visu;
}
