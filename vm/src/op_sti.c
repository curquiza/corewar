#include "vm.h"

/*
** Sti : indirect store in memory. Stores p1 at (p2 + p3) address.
** p1 = reg
** p2 = reg | dir | ind
** p3 = reg | dir
*/

void	store_4bytes_sti(t_vm *vm, int16_t index, int value,
							t_processus *proc)
{
	t_memcase	op_case;

	index += MEM_SIZE;
	op_case = vm->memory[proc->pc];

	vm->memory[index % MEM_SIZE].value = (t_byte) ((value >> 24) & 0xff);
	ft_strcpy(vm->memory[index % MEM_SIZE].color, op_case.color);
	vm->memory[index % MEM_SIZE].color_visu = op_case.color_visu;

	index += 1;
	vm->memory[index % MEM_SIZE].value = (t_byte) ((value >> 16) & 0xff);
	ft_strcpy(vm->memory[index % MEM_SIZE].color, op_case.color);
	vm->memory[index % MEM_SIZE].color_visu = op_case.color_visu;

	index += 1;
	vm->memory[index % MEM_SIZE].value = (t_byte) ((value >> 8) & 0xff);
	ft_strcpy(vm->memory[index % MEM_SIZE].color, op_case.color);
	vm->memory[index % MEM_SIZE].color_visu = op_case.color_visu;

	index += 1;
	vm->memory[index % MEM_SIZE].value = (t_byte) (value & 0xff);
	ft_strcpy(vm->memory[index % MEM_SIZE].color, op_case.color);
	vm->memory[index % MEM_SIZE].color_visu = op_case.color_visu;
}

/*
** Get 4 bytes according to parameter type
*/
static int	get_value_according_to_type_sti(t_vm *vm, t_processus *proc, t_param *p,
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
		return ((int16_t) rslt);
	}
	if (p->type == T_DIR)
		return ((int16_t) p->value);
	return (0);
}
void	op_sti(t_vm *vm, t_processus *proc, t_param *params)
{
	int		p1;
	int		p2;
	int		p3;

	print_str("\tExecuting STI\n", ALL, vm);
	p1 = proc->reg[params[0].value - 1];
	/*p2 = get_value_according_to_type(vm, proc, &params[1], RESTRICT);*/
	/*p3 = get_value_according_to_type(vm, proc, &params[2], RESTRICT);*/
	/*printf("p1 = %d\n", p1);*/
	p2 = get_value_according_to_type_sti(vm, proc, &params[1], RESTRICT);
	/*printf("p2 = %d\n", p2);*/
	p3 = get_value_according_to_type_sti(vm, proc, &params[2], RESTRICT);
	/*printf("p3 = %d\n", p3);*/
	/*printf("p2 + p3 = %d\n", p2 + p3);*/
	/*printf("p2 + p3 mod IDX_MOD = %d\n", (p2 + p3) % IDX_MOD);*/
	/*store_4bytes(vm, p2 + p3, p1, proc);*/
	store_4bytes_sti(vm, proc->pc + ((int16_t) ((p2 + p3) % IDX_MOD)), p1, proc);
	/*ft_printf("params[0].value %x\n", params[0].value);*/
	/*ft_printf("params[1].value %x\n", params[1].value);*/
	/*ft_printf("params[2].value %x\n", params[2].value);*/
}
