/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_display_players.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 10:52:14 by curquiza          #+#    #+#             */
/*   Updated: 2019/01/10 15:25:01 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_color_pair	get_player_color(int player_id)
{
	if (player_id == 0)
		return (CYAN_PAIR);
	else if (player_id == 1)
		return (PINK_PAIR);
	else if (player_id == 2)
		return (GREEN_PAIR);
	else
		return (YELLOW_PAIR);
}

void				display_players(t_vm *vm, WINDOW **wins)
{
	int		i;

	i = 0;
	while (i < vm->total_players)
	{
		box(wins[i], ACS_VLINE, ACS_HLINE);
		wattron(wins[i], COLOR_PAIR(get_player_color(i)));
		mvwprintw(wins[i], 1, 2, "PLAYER %d", i + 1);
		wattroff(wins[i], COLOR_PAIR(get_player_color(i)));
		mvwprintw(wins[i], 3, 2, "%-9s%12d", "Num", vm->player[i].num);
		if (ft_strlen(vm->player[i].header.prog_name) > 12)
			mvwprintw(wins[i], 4, 2, "%-9s%9.9s...", "Name",
						vm->player[i].header.prog_name);
		else
			mvwprintw(wins[i], 4, 2, "%-9s%12.12s", "Name",
						vm->player[i].header.prog_name);
		i++;
	}
}
