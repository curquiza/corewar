/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 10:51:12 by curquiza          #+#    #+#             */
/*   Updated: 2019/01/10 10:51:13 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** St : stores the value of the first parameter into the second one
** p1 = reg
** p2 = reg | ind
*/

void	op_st(t_vm *vm, t_processus *proc, t_param *params)
{
	int		v_to_st;

	print_str("\tExecuting ST\n", ALL, vm);
	v_to_st = proc->reg[params[0].value - 1];
	if (params[1].type == T_REG)
		proc->reg[params[1].value - 1] = v_to_st;
	else if (params[1].type == T_IND)
		store_4bytes(vm, params[1].value, v_to_st, proc);
}
