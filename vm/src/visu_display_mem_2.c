#include "vm.h"

void	dump_memory_mini_visu_part(t_vm *vm, WINDOW *win, int part)
{
	int			i;
	int			end;

	box(win, ACS_VLINE, ACS_HLINE);
	wmove(win, 1, 2);
	i = 0;
	end = MEM_SIZE;
	if (part == 1)
		end = bytes_per_line_visu(vm) * MINI_VISU_MEM_PART;
	else if (part == 2)
	{
		i = bytes_per_line_visu(vm) * MINI_VISU_MEM_PART;
		end = 2 * bytes_per_line_visu(vm) * MINI_VISU_MEM_PART;
	}
	else
		i = 2 * bytes_per_line_visu(vm) * MINI_VISU_MEM_PART;
	while (i < end)
	{
		print_memory_visu(i, vm, win);
		i++;
	}
	mvwprintw(stdscr, MINI_MEM_WIN_Y + 1, 2, "MEMORY PART %d/3", part);
}

void	dump_memory_visu(t_vm *vm, WINDOW *win)
{
	int			i;

	box(win, ACS_VLINE, ACS_HLINE);
	wmove(win, 1, 2);
	i = 0;
	while (i < MEM_SIZE)
	{
		print_memory_visu(i, vm, win);
		i++;
	}
}


