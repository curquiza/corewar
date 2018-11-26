#include "vm.h"

static t_visu_type		get_visu_type(t_vm *vm)
{
	if (flag_is_applied(MINI_VISU_FLAG, vm) == TRUE)
		return (MINI_V);
	return (DEF_V);
}

static t_bool	check_term_size(void)
{
	return (LINES >= VISU_LINES && COLS >= VISU_COLS);
}

static void		print_visu_err(char *err)
{
	endwin();
	ft_dprintf(2, "Error: %s\n", err);
}

static int		bytes_per_line(t_vm *vm)
{
	// if visu = mini return 32
	(void)vm;
	return (BYTES_PER_LINE_64);
}

static void	handle_newline(int i, t_vm *vm)
{
	int		b_per_line;

	b_per_line = i % bytes_per_line(vm);
	if (b_per_line == bytes_per_line(vm) - 1)
		addch('\n');
	else
		addch(' ');
}

static void	print_mem_addr_visu(int i, t_vm *vm)
{
	if (i % bytes_per_line(vm) == 0)
		printw("0x%0.4x |\t", i);
}

void	dump_memory_visu(t_vm *vm)
{
	int			i;
	t_memcase	*memory;

	memory = vm->memory;
	i = 0;
	while (i < MEM_SIZE)
	{
		print_mem_addr_visu(i, vm);
		attron(COLOR_PAIR(memory[i].color_visu));
		printw("%0.2x", (t_byte) memory[i].value);
		attroff(COLOR_PAIR(memory[i].color_visu));
		handle_newline(i, vm);
		i++;
	}
}

void	start_visu(t_vm *vm)
{
	vm->visu.enabled = TRUE;
	vm->visu.type = get_visu_type(vm);
	initscr();
	if (has_colors() == FALSE)
		print_visu_err(VISU_COLOR_ERR);
	else if (check_term_size() == FALSE)
		print_visu_err(VISU_SIZE_ERR);
	else
	{
		start_color();
		init_pair(DEF_PAIR, COLOR_WHITE, COLOR_BLACK);
		init_pair(CYAN_PAIR, COLOR_CYAN, COLOR_BLACK);
		init_pair(PINK_PAIR, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(GREEN_PAIR, COLOR_GREEN, COLOR_BLACK);
		init_pair(YELLOW_PAIR, COLOR_YELLOW, COLOR_BLACK);
		dump_memory_visu(vm);
		getch();
		endwin();
	}
}
