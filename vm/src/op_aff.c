/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 10:50:26 by curquiza          #+#    #+#             */
/*   Updated: 2019/01/10 10:50:27 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Aff : display the value in register as character (moduo 256)
** p1 = reg
*/

void	op_aff(t_vm *vm, t_processus *proc, t_param *params)
{
	int		reg_value;

	reg_value = proc->reg[params[0].value - 1];
	ft_dprintf(vm->trace_fd, "%c\n", reg_value % 256);
}
