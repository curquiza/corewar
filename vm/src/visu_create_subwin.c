#include "vm.h"

void	create_visu_subwin(t_vm *vm)
{
	int		i;

	vm->visu.mem_win = subwin(stdscr, MEM_WIN_Y, MEM_WIN_X, 1, 1);
	vm->visu.cycles_win = subwin(stdscr, CYCLES_WIN_Y, CYCLES_WIN_X, 1, MEM_WIN_X + 20);
	vm->visu.lives_win = subwin(stdscr, LIVES_WIN_Y, LIVES_WIN_X, 1, MEM_WIN_X + 50);
	vm->visu.proc_win = subwin(stdscr, PROC_WIN_Y, PROC_WIN_X, 1, MEM_WIN_X + 80);
	vm->visu.usage_win = subwin(stdscr, USAGE_WIN_Y, USAGE_WIN_X, PROC_WIN_Y + 5, MEM_WIN_X + 80);
	i = 0;
	while (i < vm->total_players)
	{
		vm->visu.players_win[i] = subwin(stdscr, PLAYER_WIN_Y, PLAYER_WIN_X, CYCLES_WIN_Y + 5 + i * PLAYER_WIN_Y, MEM_WIN_X + 20);
		i++;
	}
}

void	create_mini_visu_subwin(t_vm *vm)
{
	int		i;

	vm->visu.mem_win = subwin(stdscr, MINI_MEM_WIN_Y, MINI_MEM_WIN_X, 1, 1);
	vm->visu.cycles_win = subwin(stdscr, CYCLES_WIN_Y, CYCLES_WIN_X, 1, MINI_MEM_WIN_X + 20);
	vm->visu.lives_win = subwin(stdscr, LIVES_WIN_Y, LIVES_WIN_X, 1, MINI_MEM_WIN_X + 50);
	vm->visu.proc_win = subwin(stdscr, PROC_WIN_Y, PROC_WIN_X, LIVES_WIN_Y + 5, MINI_MEM_WIN_X + 50);
	vm->visu.usage_win = subwin(stdscr, USAGE_WIN_Y, USAGE_WIN_X, LINES - USAGE_WIN_Y - 1, MINI_MEM_WIN_X + 1);
	i = 0;
	while (i < vm->total_players)
	{
		vm->visu.players_win[i] = subwin(stdscr, PLAYER_WIN_Y, PLAYER_WIN_X, CYCLES_WIN_Y + 5 + i * PLAYER_WIN_Y, MINI_MEM_WIN_X + 20);
		i++;
	}
}
