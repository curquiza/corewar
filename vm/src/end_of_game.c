#include "vm.h"

static t_player	*get_player(int num, t_player *players, int total_players)
{
	int		i;

	i = 0;
	while (i < total_players)
	{
		if (players[i].num == num)
			return (&players[i]);
		i++;
	}
	return (NULL);
}

static void		print_visu_rslt(t_vm *vm, WINDOW *win, int i)
{
	t_player	*p;

	box(win, ACS_VLINE, ACS_HLINE);
	mvwprintw(win, 2, (END_WIN_X - 11) / 2, "END OF GAME");
	if (vm->last_live_player == -1)
	{
		mvwprintw(win, 5, (END_WIN_X - 12) / 2, "Nobody won !");
		mvwprintw(win, 7, (END_WIN_X - 3) / 2, "T.T");
	}
	else
	{
		p = get_player(vm->last_live_player, vm->player, vm->total_players);
		if (ft_strlen(p->header.prog_name) > 12)
			mvwprintw(win, 5, (END_WIN_X - 26) / 2, "Player \"%.9s...\" won !",
						p->header.prog_name);
		else
			mvwprintw(win, 5,
						(END_WIN_X - (12 + ft_strlen(p->header.prog_name))) / 2,
						"Player \"%s\" won !", p->header.prog_name);
		
		mvwprintw(win, 7, (END_WIN_X - 3) / 2, "^.^");
	}
	mvwprintw(win, 10, (END_WIN_X - 18) / 2, "Quitting in %d s...", i);
}

static void		visu_end(t_vm *vm)
{
	WINDOW	*end_win;
	int		i;

	end_win = subwin(stdscr, END_WIN_Y, END_WIN_X, (LINES - END_WIN_Y) / 2,
					(COLS - END_WIN_X)  / 2);
	i = 5;
	while (i != 0)
	{
		werase(end_win);
		print_visu_rslt(vm, end_win, i);
		wrefresh(end_win);
		sleep(1);
		i--;
	}
	endwin();
	if (vm->trace_fd != STDOUT_FILENO)
		close(vm->trace_fd);
}

void		end_of_game(t_vm *vm)
{
	t_player	*p;

	if (vm->run != BREAK)
	{
		if (vm->last_live_player == -1)
			ft_dprintf(vm->trace_fd, "Nobody won !\n");
		else
		{
			p = get_player(vm->last_live_player, vm->player, vm->total_players);
			ft_dprintf(vm->trace_fd, "Player %d (%s) won !\n", vm->last_live_player, p->header.prog_name);
		}
		ft_dprintf(vm->trace_fd, "End of game. Thanks for watching 😎\n");
	}
	if (vm->visu.enabled == TRUE)
		visu_end(vm);
}
