#include "vm.h"

/*
** Sti : indirect store in memory. Stores p1 at (p2 + p3) address.
** p1 = reg
** p2 = reg | dir | ind
** p3 = reg | dir
*/


/*static unsigned short	get_index_according_to_type(t_vm *vm, t_processus *proc, t_param *p)*/
/*{*/
	/*unsigned short	rslt;*/

	/*if (p->type == T_DIR)*/
		/*return ((unsigned short) p->value);*/
	/*if (p->type == T_IND)*/
	/*{*/
		/*// /!\ IDX_MOD ??*/
		/*rslt = memvalue_to_uint32(vm->memory, proc->pc + (p->value % IDX_MOD), IND_SIZE);*/
		/*return (rslt);*/
	/*}*/
	/*if (p->type == T_REG && is_valid_reg_index(p->value))*/
		/*return ((unsigned short) proc->reg[p->value - 1]);*/
	/*return (0);*/
/*}*/

static void	store_4bytes(t_vm *vm, unsigned short index, int value,
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

void	op_sti(t_vm *vm, t_processus *proc, t_param *params)
{
	int		p1;
	int		p2;
	int		p3;

	print_str("\tExecuting STI\n", ALL, vm);
	// si p1 n'est pas un invalid index de registre ???
	p1 = 0;
	if (is_valid_reg_index(params[0].value) == TRUE)
		p1 = proc->reg[params[0].value - 1];
	p2 = get_value_according_to_type(vm, proc, &params[1]);
	p3 = get_value_according_to_type(vm, proc, &params[2]);
	// /!\ faut il faire ((p2 + p3) % IDX_MOD) ???
	store_4bytes(vm, (unsigned short) (proc->pc + (p2 + p3)), p1, proc);
	ft_dprintf(vm->trace_fd, "p1 = 0x%x\n", p1); //DEBUG
	ft_dprintf(vm->trace_fd, "p2 = %x\n", p2);   //DEBUG
	ft_dprintf(vm->trace_fd, "p3 = %d\n", p3);   //DEBUG
}
