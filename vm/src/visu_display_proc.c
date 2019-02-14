/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_display_proc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 10:52:17 by curquiza          #+#    #+#             */
/*   Updated: 2019/01/10 15:48:51 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	display_title(t_vm *vm, int proc_id, WINDOW *win)
{
	if (vm->total_proc < 10)
		mvwprintw(win, 1, 2, "%-15s%4d/%d", "PROCESSUS", proc_id,
			vm->total_proc);
	else if (vm->total_proc < 100)
		mvwprintw(win, 1, 2, "%-15s%3d/%d", "PROCESSUS", proc_id,
			vm->total_proc);
	else
		mvwprintw(win, 1, 2, "%-15s%2d/%d", "PROCESSUS", proc_id,
			vm->total_proc);
}

void		display_proc(t_vm *vm, int proc_id, WINDOW *win)
{
	int			i;
	t_processus	*proc;

	if (vm->proc == NULL)
		return ;
	proc = vm->proc;
	i = 1;
	while (proc && i++ != proc_id)
		proc = proc->next;
	box(win, ACS_VLINE, ACS_HLINE);
	display_title(vm, proc_id, win);
	mvwprintw(win, 3, 2, "%-15s%6d", "PC", proc->pc);
	mvwprintw(win, 4, 2, "%-15s%6d", "Carry", proc->carry);
	mvwprintw(win, 5, 2, "%-15s%6s", "Alive ?", proc->live ? "Yes" : "No");
	if (proc->current_op)
		mvwprintw(win, 7, 2, "%-15s%6s", "Op", proc->current_op->name);
	else
		mvwprintw(win, 7, 2, "%-15s%6s", "Op", "None");
	mvwprintw(win, 8, 2, "%-15s%6d", "Cycles", proc->cycles);
	i = 0;
	while (i < REG_NUMBER)
	{
		mvwprintw(win, 10 + i, 2, "R%-9.2d 0x%.8x", i + 1, proc->reg[i]);
		i++;
	}
}
