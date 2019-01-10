/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_display_lives.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 10:52:07 by curquiza          #+#    #+#             */
/*   Updated: 2019/01/10 10:52:08 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	display_lives(t_vm *vm, WINDOW *win)
{
	t_player	*p;

	box(win, ACS_VLINE, ACS_HLINE);
	mvwprintw(win, 1, 10, "LIVES");
	mvwprintw(win, 2, 2, "---------------------");
	mvwprintw(win, 4, 2, "%-15s%6d", "Total", vm->lives);
	mvwprintw(win, 5, 2, "%-15s%6d", "Verif", vm->verif);
	if (vm->last_live_player == -1)
		mvwprintw(win, 6, 2, "%-15s%6s", "Last", "None");
	else
	{
		p = get_player(vm->last_live_player, vm->player, vm->total_players);
		if (ft_strlen(p->header.prog_name) > 12)
			mvwprintw(win, 6, 2, "%-9s%9.9s...", "Last", p->header.prog_name);
		else
			mvwprintw(win, 6, 2, "%-9s%12s", "Last", p->header.prog_name);
	}
	mvwprintw(win, 8, 2, "%-15s%6d", "Min lives", NBR_LIVE);
	mvwprintw(win, 9, 2, "%-15s%6d", "Max checks", MAX_CHECKS);
}
