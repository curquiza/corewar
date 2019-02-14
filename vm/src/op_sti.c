/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 10:51:15 by curquiza          #+#    #+#             */
/*   Updated: 2019/01/10 13:18:10 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Sti : indirect store in memory. Stores p1 at (p2 + p3) address.
** p1 = reg
** p2 = reg | dir | ind
** p3 = reg | dir
*/

void		store_4bytes_sti(t_vm *vm, int16_t index, int value,
							t_processus *proc)
{
	t_memcase	op_case;

	index += MEM_SIZE;
	op_case = vm->memory[proc->pc];
	vm->memory[index % MEM_SIZE].value = (t_byte)((value >> 24) & 0xff);
	ft_strcpy(vm->memory[index % MEM_SIZE].color, op_case.color);
	vm->memory[index % MEM_SIZE].color_visu = op_case.color_visu;
	index += 1;
	vm->memory[index % MEM_SIZE].value = (t_byte)((value >> 16) & 0xff);
	ft_strcpy(vm->memory[index % MEM_SIZE].color, op_case.color);
	vm->memory[index % MEM_SIZE].color_visu = op_case.color_visu;
	index += 1;
	vm->memory[index % MEM_SIZE].value = (t_byte)((value >> 8) & 0xff);
	ft_strcpy(vm->memory[index % MEM_SIZE].color, op_case.color);
	vm->memory[index % MEM_SIZE].color_visu = op_case.color_visu;
	index += 1;
	vm->memory[index % MEM_SIZE].value = (t_byte)(value & 0xff);
	ft_strcpy(vm->memory[index % MEM_SIZE].color, op_case.color);
	vm->memory[index % MEM_SIZE].color_visu = op_case.color_visu;
}

static int	get_value_according_to_type_sti(t_vm *vm, t_processus *proc,
											t_param *p)
{
	int		rslt;

	if (p->type == T_REG && is_valid_reg_index(p->value))
		return (proc->reg[p->value - 1]);
	if (p->type == T_IND)
	{
		rslt = memvalue_to_int32_restrict(vm->memory, proc, p->value, REG_SIZE);
		return ((int16_t)rslt);
	}
	if (p->type == T_DIR)
		return ((int16_t)p->value);
	return (0);
}

void		op_sti(t_vm *vm, t_processus *proc, t_param *params)
{
	int		p1;
	int		p2;
	int		p3;

	print_str("\tExecuting STI\n", ALL, vm);
	p1 = proc->reg[params[0].value - 1];
	p2 = get_value_according_to_type_sti(vm, proc, &params[1]);
	p3 = get_value_according_to_type_sti(vm, proc, &params[2]);
	store_4bytes_sti(vm, proc->pc + ((int16_t)((p2 + p3) % IDX_MOD)), p1, proc);
}
