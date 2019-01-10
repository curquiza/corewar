/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 10:50:45 by curquiza          #+#    #+#             */
/*   Updated: 2019/01/10 13:23:45 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Lfork : fork the current processus with no address restriction
** p1 = dir
** No OCP
*/

void	op_lfork(t_vm *vm, t_processus *proc, t_param *params)
{
	t_processus		*new_proc;
	size_t			len;

	new_proc = new_processus(get_mem_index(proc, params[0].value, DEF_ADDR),
							vm);
	new_proc->live = proc->live;
	new_proc->carry = proc->carry;
	len = REG_NUMBER * sizeof(*proc->reg);
	ft_memmove(new_proc->reg, proc->reg, len);
	add_processus(&vm->proc, new_proc);
}
