#include "vm.h"

static t_bool	check_term_size(void)
{
	return (LINES >= MINI_VISU_LINES && COLS >= MINI_VISU_COLS);
}

static t_visu_type		get_visu_type(void)
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

static int		bytes_per_line(t_vm *vm)
{
	if (vm->visu.type == MINI_V)
		return (BYTES_PER_LINE_32);
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
		printw("0x%0.4x |   ", i);
}

static void	init_visu(t_vm *vm)
{
	vm->visu.enabled = TRUE;
	vm->visu.type = get_visu_type();
	start_color();
	init_pair(DEF_PAIR, COLOR_WHITE, COLOR_BLACK);
	init_pair(CYAN_PAIR, COLOR_CYAN, COLOR_BLACK);
	init_pair(PINK_PAIR, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(GREEN_PAIR, COLOR_GREEN, COLOR_BLACK);
	init_pair(YELLOW_PAIR, COLOR_YELLOW, COLOR_BLACK);
}

static int	get_attr(t_memcase *memory)
{
	if (memory->proc == TRUE)
		return (COLOR_PAIR(memory->color_visu) | A_STANDOUT);
	return (COLOR_PAIR(memory->color_visu));
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
		attron(get_attr(&memory[i]));
		printw("%0.2x", (t_byte) memory[i].value);
		attroff(get_attr(&memory[i]));
		handle_newline(i, vm);
		i++;
	}
}

void	display_cycles(t_vm *vm, int y_pos, int x_pos)
{
	mvprintw(y_pos, x_pos, "CYCLES");
	mvprintw(y_pos + 2, x_pos, "%-15s%d", "Total", vm->total_cycles);
	mvprintw(y_pos + 3, x_pos, "%-15s%d", "Current", vm->current_cycles);
	mvprintw(y_pos + 5, x_pos, "%-15s%d", "Cycle to die", vm->cycles_to_die);
	mvprintw(y_pos + 6, x_pos, "%-15s%d", "Cycle delta", CYCLE_DELTA);
}

void	display_lives(t_vm *vm, int y_pos, int x_pos)
{
	mvprintw(y_pos, x_pos, "LIVES");
	mvprintw(y_pos + 2, x_pos, "%-15s%d", "Total", vm->lives);
	mvprintw(y_pos + 3, x_pos, "%-15s%d", "Last player", vm->last_live_player_id);
	mvprintw(y_pos + 4, x_pos, "%-15s%d", "Verif", vm->verif);
	mvprintw(y_pos + 6, x_pos, "%-15s%d", "Min lives", NBR_LIVE);
	mvprintw(y_pos + 7, x_pos, "%-15s%d", "Max checks", MAX_CHECKS);
}

void	display_proc(t_processus *proc, int y_pos, int x_pos, t_vm *vm, int proc_id)
{
	int		i;

	i = 0;
	mvprintw(y_pos, x_pos, "%-15s%d/%d", "PROCESSUS", proc_id, vm->total_proc);
	mvprintw(y_pos + 2, x_pos, "%-15s%d", "PC", proc->pc);
	mvprintw(y_pos + 3, x_pos, "%-15s%d", "Index", proc->index);
	mvprintw(y_pos + 4, x_pos, "%-15s%s", "Live", proc->live ? "Yes" : "No");
	mvprintw(y_pos + 5, x_pos, "%-15s0x%0.2x", "Opcode", proc->opcode);
	mvprintw(y_pos + 6, x_pos, "%-15s%d", "Cycles", proc->cycles);
	while (i < REG_NUMBER)
	{
		mvprintw(y_pos + i + 8, x_pos, "R%-13.2d %d", i + 1, proc->reg[i]);
		i++;
	}
}

void	display_visu(t_vm *vm)
{
	int		bpl;
	int		x_pos;

	move(1, 0);
	dump_memory_visu(vm);
	bpl = bytes_per_line(vm);
	x_pos = 11 + bpl * 2 + bpl + 10;
	display_cycles(vm, 1, x_pos);
	display_lives(vm, 1, x_pos + 30);
	display_proc(vm->proc, 1, x_pos + 60, vm, 1);
	curs_set(0);
}

void	start_visu(t_vm *vm)
{
	initscr();
	if (has_colors() == FALSE)
		print_visu_err(VISU_COLOR_ERR);
	else if (check_term_size() == FALSE)
		print_visu_err(VISU_SIZE_ERR);
	else
	{
		init_visu(vm);
		display_visu(vm);
		getch();
	}
}
