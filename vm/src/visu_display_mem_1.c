#include "vm.h"

static int	get_attr(t_memcase *memory)
{
	if (memory->proc == TRUE)
		return (COLOR_PAIR(memory->color_visu) | A_STANDOUT);
	return (COLOR_PAIR(memory->color_visu));
}

int			bytes_per_line_visu(t_vm *vm)
{
	if (vm->visu.type == MINI_V)
		return (BYTES_PER_LINE_32);
	return (BYTES_PER_LINE_64);
}

static void	print_mem_addr_visu(int i, t_vm *vm, WINDOW *win)
{
	if (i % bytes_per_line_visu(vm) == 0)
		wprintw(win, "0x%0.4x |   ", i);
}

static void	handle_newline(int i, t_vm *vm, WINDOW *win)
{
	int		b_per_line;
	int		x;
	int		y;

	b_per_line = i % bytes_per_line_visu(vm);
	if (b_per_line == bytes_per_line_visu(vm) - 1)
	{
		getyx(win, y, x);
		wmove(win, y + 1, 2);
	}
	else
		waddch(win, ' ');
}

void	print_memory_visu(int i, t_vm *vm, WINDOW *win)
{
	t_memcase	*memory;

	memory = vm->memory;
	print_mem_addr_visu(i, vm, win);
	wattron(win, get_attr(&memory[i]));
	wprintw(win, "%0.2x", (t_byte) memory[i].value);
	wattroff(win, get_attr(&memory[i]));
	handle_newline(i, vm, win);
}
