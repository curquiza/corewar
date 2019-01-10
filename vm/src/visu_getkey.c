/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_getkey.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 10:52:22 by curquiza          #+#    #+#             */
/*   Updated: 2019/01/10 10:56:22 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	toogle_pause(t_vm *vm)
{
	if (vm->visu.pause)
	{
		vm->visu.pause = FALSE;
		nodelay(stdscr, TRUE);
	}
	else
	{
		vm->visu.pause = TRUE;
		nodelay(stdscr, FALSE);
	}
}

void		getkey(t_vm *vm)
{
	char	c;

	c = getch();
	if (c == 'n')
		vm->visu.next_step = TRUE;
	else if (c == ' ')
		toogle_pause(vm);
	else if (c == 'm' && vm->visu.type == MINI_V)
		vm->visu.mem_part = vm->visu.mem_part % 3 + 1;
	else if (c == 'p')
		vm->visu.proc_id = vm->visu.proc_id % vm->total_proc + 1;
	else if (c == 'P')
	{
		if (vm->visu.proc_id - 1 == 0)
			vm->visu.proc_id = vm->total_proc;
		else
			vm->visu.proc_id = vm->visu.proc_id - 1;
	}
}
