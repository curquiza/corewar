#include "vm.h"

/*
** Handle vm circle memory and address restriction
*/
int		get_mem_index(t_processus *proc, signed short index, t_addr_type addr)
{
	unsigned short		tmp;

	if (addr != RESTRICT)
		return ((proc->pc + (unsigned short) index) % MEM_SIZE);
	tmp = (unsigned short) (proc->pc + (index % IDX_MOD));
	/*ft_dprintf(1, "index = %d\n", index);*/
	/*printf("index mod IDX_MOD = %d\n", index % IDX_MOD);*/
	return (tmp % MEM_SIZE);
}

/*
** Check if index is a valid register number
*/
t_bool	is_valid_reg_index(int index)
{
	return (index > 0 && index <= REG_NUMBER);
}

/*
** Get 4 bytes according to parameter type
*/
int	get_value_according_to_type(t_vm *vm, t_processus *proc, t_param *p,
								t_addr_type addr_type)
{
	int		rslt;

	if (p->type == T_REG && is_valid_reg_index(p->value))
		return (proc->reg[p->value - 1]);
	if (p->type == T_IND)
	{
		if (addr_type == RESTRICT)
			rslt = memvalue_to_int32_restrict(vm->memory, proc, p->value,
											REG_SIZE);
		else
			rslt = memvalue_to_int32_norestrict(vm->memory, proc, p->value,
											REG_SIZE);
		return (rslt);
	}
	if (p->type == T_DIR)
		return (p->value);
	return (0);
}

/*
** Store 4 bytes in memory
** Address restriction
*/

void	store_4bytes(t_vm *vm, signed short index, int value,
							t_processus *proc)
{
	t_memcase	op_case;
	signed short	tmp_index;

	op_case = vm->memory[proc->pc];
	vm->memory[get_mem_index(proc, index, RESTRICT)].value = (t_byte) ((value >> 24) & 0xff);
	ft_strcpy(vm->memory[get_mem_index(proc, index, RESTRICT)].color, op_case.color);
	vm->memory[get_mem_index(proc, index, RESTRICT)].color_visu = op_case.color_visu;

	tmp_index = get_mem_index(proc, index, RESTRICT) - proc->pc + 1;
	vm->memory[get_mem_index(proc, tmp_index, DEF_ADDR)].value = (t_byte) ((value >> 16) & 0xff);
	ft_strcpy(vm->memory[get_mem_index(proc, tmp_index, DEF_ADDR)].color, op_case.color);
	vm->memory[get_mem_index(proc, tmp_index, DEF_ADDR)].color_visu = op_case.color_visu;

	tmp_index += 1;
	vm->memory[get_mem_index(proc, tmp_index, DEF_ADDR)].value = (t_byte) ((value >> 8) & 0xff);
	ft_strcpy(vm->memory[get_mem_index(proc, tmp_index, DEF_ADDR)].color, op_case.color);
	vm->memory[get_mem_index(proc, tmp_index, DEF_ADDR)].color_visu = op_case.color_visu;

	tmp_index += 1;
	vm->memory[get_mem_index(proc, tmp_index, DEF_ADDR)].value = (t_byte) (value & 0xff);
	ft_strcpy(vm->memory[get_mem_index(proc, tmp_index, DEF_ADDR)].color, op_case.color);
	vm->memory[get_mem_index(proc, tmp_index, DEF_ADDR)].color_visu = op_case.color_visu;
}
