/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 10:50:32 by curquiza          #+#    #+#             */
/*   Updated: 2019/01/10 13:17:21 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Fork : fork the current processus
** p1 = dir
** No OCP
*/

void	op_fork(t_vm *vm, t_processus *proc, t_param *params)
{
	size_t			len;
	t_processus		*new_proc;

	new_proc = new_processus(get_mem_index(proc, params[0].value, RESTRICT),
							vm);
	new_proc->live = proc->live;
	new_proc->carry = proc->carry;
	len = REG_NUMBER * sizeof(*proc->reg);
	ft_memmove(new_proc->reg, proc->reg, len);
	add_processus(&vm->proc, new_proc);
}
