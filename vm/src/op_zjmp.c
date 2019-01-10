/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 20:21:22 by curquiza          #+#    #+#             */
/*   Updated: 2019/01/09 20:21:25 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Zjmp : jump until the address passed in parameter
** No OCP
** p1 = dir
*/

void	op_zjmp(t_vm *vm, t_processus *proc, t_param *params)
{
	print_str("\tExecuting ZJMP\n", ALL, vm);
	if (proc->carry == 1)
		proc->pc = get_mem_index(proc, params[0].value, RESTRICT);
}
