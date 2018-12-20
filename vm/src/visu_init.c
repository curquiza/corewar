#include "vm.h"

static t_bool		check_term_size(void)
{
	return (LINES >= MINI_VISU_LINES && COLS >= MINI_VISU_COLS);
}

static t_visu_type	get_visu_type(void)
{
	if (LINES < VISU_LINES || COLS < VISU_COLS)
		return (MINI_V);
	return (DEF_V);
}

static void		print_visu_err(char *err)
{
	endwin();
	ft_dprintf(2, "Error: %s\n", err);
}

static void	init_visu(t_vm *vm)
{
	vm->visu.enabled = TRUE;
	vm->visu.pause = TRUE;
	vm->visu.type = get_visu_type();
	vm->visu.mem_part = 1;
	vm->visu.proc_id = 1;
	start_color();
	init_pair(DEF_PAIR, COLOR_WHITE, COLOR_BLACK);
	init_pair(CYAN_PAIR, COLOR_CYAN, COLOR_BLACK);
	init_pair(PINK_PAIR, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(GREEN_PAIR, COLOR_GREEN, COLOR_BLACK);
	init_pair(YELLOW_PAIR, COLOR_YELLOW, COLOR_BLACK);
	if (vm->visu.type == DEF_V)
		create_visu_subwin(vm);
	else
		create_mini_visu_subwin(vm);
	noecho();
	curs_set(0);
	nodelay(stdscr, FALSE);
}

void	start_visu(t_vm *vm)
{
	initscr();
	if (has_colors() == FALSE)
	{
		print_visu_err(VISU_COLOR_ERR);
		vm->trace_fd = STDOUT_FILENO;
	}
	else if (check_term_size() == FALSE)
	{
		print_visu_err(VISU_SIZE_ERR);
		vm->trace_fd = STDOUT_FILENO;
	}
	else
	{
		init_visu(vm);
		display_visu(vm);
	}
}
