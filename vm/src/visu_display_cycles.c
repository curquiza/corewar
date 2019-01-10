/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_display_cycles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 10:52:05 by curquiza          #+#    #+#             */
/*   Updated: 2019/01/10 10:52:06 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	display_cycles(t_vm *vm, WINDOW *win)
{
	box(win, ACS_VLINE, ACS_HLINE);
	mvwprintw(win, 1, 9, "CYCLES");
	mvwprintw(win, 2, 2, "---------------------");
	mvwprintw(win, 4, 2, "%-15s%6d", "Total", vm->total_cycles);
	mvwprintw(win, 5, 2, "%-15s%6d", "Current", vm->current_cycles);
	mvwprintw(win, 7, 2, "%-15s%6d", "Cycle to die", vm->cycles_to_die);
	mvwprintw(win, 8, 2, "%-15s%6d", "Cycle delta", CYCLE_DELTA);
}
