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

static void	handle_newline(int i, t_vm *vm, WINDOW *win)
{
	int		b_per_line;
	int		x;
	int		y;

	b_per_line = i % bytes_per_line(vm);
	if (b_per_line == bytes_per_line(vm) - 1)
	{
		getyx(win, y, x);
		wmove(win, y + 1, 2);
	}
	else
		waddch(win, ' ');
}

static void	print_mem_addr_visu(int i, t_vm *vm, WINDOW *win)
{
	if (i % bytes_per_line(vm) == 0)
		wprintw(win, "0x%0.4x |   ", i);
}

static void	create_visu_boxes(t_vm *vm)
{
	int		i;

	vm->visu.mem_win = subwin(stdscr, MEM_WIN_Y, MEM_WIN_X, 1, 1);
	vm->visu.cycles_win = subwin(stdscr, CYCLES_WIN_Y, CYCLES_WIN_X, 1, MEM_WIN_X + 20);
	box(vm->visu.cycles_win, ACS_VLINE, ACS_HLINE);
	vm->visu.lives_win = subwin(stdscr, LIVES_WIN_Y, LIVES_WIN_X, 1, MEM_WIN_X + 50);
	box(vm->visu.lives_win, ACS_VLINE, ACS_HLINE);
	vm->visu.proc_win = subwin(stdscr, PROC_WIN_Y, PROC_WIN_X, 1, MEM_WIN_X + 80);
	box(vm->visu.proc_win, ACS_VLINE, ACS_HLINE);
	i = 0;
	while (i < vm->total_players)
	{
		vm->visu.players_win[i] = subwin(stdscr, PLAYER_WIN_Y, PLAYER_WIN_X, CYCLES_WIN_Y + 5 + i * PLAYER_WIN_Y, MEM_WIN_X + 20);
		box(vm->visu.players_win[i], ACS_VLINE, ACS_HLINE);
		i++;
	}
}

static void	create_mini_visu_boxes(t_vm *vm)
{
	int		i;

	vm->visu.mem_win = subwin(stdscr, MINI_MEM_WIN_Y, MINI_MEM_WIN_X, 1, 1);
	vm->visu.cycles_win = subwin(stdscr, CYCLES_WIN_Y, CYCLES_WIN_X, 1, MINI_MEM_WIN_X + 20);
	vm->visu.lives_win = subwin(stdscr, LIVES_WIN_Y, LIVES_WIN_X, 1, MINI_MEM_WIN_X + 50);
	vm->visu.proc_win = subwin(stdscr, PROC_WIN_Y, PROC_WIN_X, LIVES_WIN_Y + 5, MINI_MEM_WIN_X + 50);
	i = 0;
	while (i < vm->total_players)
	{
		vm->visu.players_win[i] = subwin(stdscr, PLAYER_WIN_Y, PLAYER_WIN_X, CYCLES_WIN_Y + 5 + i * PLAYER_WIN_Y, MINI_MEM_WIN_X + 20);
		i++;
	}
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
	if (vm->visu.type == DEF_V)
		create_visu_boxes(vm);
	else
		create_mini_visu_boxes(vm);
}

static int	get_attr(t_memcase *memory)
{
	if (memory->proc == TRUE)
		return (COLOR_PAIR(memory->color_visu) | A_STANDOUT);
	return (COLOR_PAIR(memory->color_visu));
}

static void	print_memory_visu(int i, t_vm *vm, WINDOW *win)
{
	t_memcase	*memory;

	memory = vm->memory;
	print_mem_addr_visu(i, vm, win);
	wattron(win, get_attr(&memory[i]));
	wprintw(win, "%0.2x", (t_byte) memory[i].value);
	wattroff(win, get_attr(&memory[i]));
	handle_newline(i, vm, win);
}

static void	dump_memory_mini_visu_part(t_vm *vm, WINDOW *win, int part)
{
	int			i;
	int			end;

	box(win, ACS_VLINE, ACS_HLINE);
	wmove(win, 1, 2);
	i = 0;
	end = MEM_SIZE;
	if (part == 1)
		end = bytes_per_line(vm) * MINI_VISU_MEM_PART;
	else if (part == 2)
	{
		i = bytes_per_line(vm) * MINI_VISU_MEM_PART;
		end = 2 * bytes_per_line(vm) * MINI_VISU_MEM_PART;
	}
	else
		i = 2 * bytes_per_line(vm) * MINI_VISU_MEM_PART;
	while (i < end)
	{
		print_memory_visu(i, vm, win);
		i++;
	}
	mvwprintw(stdscr, LINES - 1, 2, "MEMORY PART %d/3", part);
}

static void	dump_memory_visu(t_vm *vm, WINDOW *win)
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

static void	display_cycles(t_vm *vm, WINDOW *win)
{
	box(win, ACS_VLINE, ACS_HLINE);
	mvwprintw(win, 1, 9, "CYCLES");
	mvwprintw(win, 2, 2, "---------------------");
	mvwprintw(win, 4, 2, "%-15s%d", "Total", vm->total_cycles);
	mvwprintw(win, 5, 2, "%-15s%d", "Current", vm->current_cycles);
	mvwprintw(win, 7, 2, "%-15s%d", "Cycle to die", vm->cycles_to_die);
	mvwprintw(win, 8, 2, "%-15s%d", "Cycle delta", CYCLE_DELTA);
}

static void	display_lives(t_vm *vm, WINDOW *win)
{
	box(win, ACS_VLINE, ACS_HLINE);
	mvwprintw(win, 1, 10, "LIVES");
	mvwprintw(win, 2, 2, "---------------------");
	mvwprintw(win, 4, 2, "%-15s%d", "Total", vm->lives);
	mvwprintw(win, 5, 2, "%-15s%d", "Verif", vm->verif);
	mvwprintw(win, 6, 2, "%-15s%d", "Last player", vm->last_live_player_id);
	mvwprintw(win, 8, 2, "%-15s%d", "Min lives", NBR_LIVE);
	mvwprintw(win, 9, 2, "%-15s%d", "Max checks", MAX_CHECKS);
}

static void	display_proc(t_processus *proc, t_vm *vm, int proc_id, WINDOW *win)
{
	int		i;

	box(win, ACS_VLINE, ACS_HLINE);
	mvwprintw(win, 1, 2, "%-15s%d/%d", "PROCESSUS", proc_id, vm->total_proc);
	mvwprintw(win, 3, 2, "%-15s%d", "PC", proc->pc);
	mvwprintw(win, 4, 2, "%-15s%d", "Index", proc->index);
	mvwprintw(win, 5, 2, "%-15s%s", "Live", proc->live ? "Yes" : "No");
	mvwprintw(win, 6, 2, "%-15s0x%0.2x", "Opcode", proc->opcode);
	mvwprintw(win, 7, 2, "%-15s%d", "Cycles", proc->cycles);
	i = 0;
	while (i < REG_NUMBER)
	{
		mvwprintw(win, 9 + i, 2, "R%-13.2d %d", i + 1, proc->reg[i]);
		i++;
	}
}

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

static void	display_players(t_vm *vm, WINDOW **wins)
{
	int		i;

	i = 0;
	while (i < vm->total_players)
	{
		box(wins[i], ACS_VLINE, ACS_HLINE);
		wattron(wins[i], COLOR_PAIR(get_player_color(i)));
		mvwprintw(wins[i], 1, 2, "PLAYER %d", vm->player[i].num);
		wattroff(wins[i], COLOR_PAIR(get_player_color(i)));
		mvwprintw(wins[i], 3, 2, "%-15s%s", "Name", vm->player[i].header.prog_name);
		mvwprintw(wins[i], 4, 2, "%-15s%d", "Prog size", vm->player[i].header.prog_size);
		i++;
	}
}

static void	display_visu(t_vm *vm)
{
	if (vm->visu.type == MINI_V)
		dump_memory_mini_visu_part(vm, vm->visu.mem_win, 1);
	else
		dump_memory_visu(vm, vm->visu.mem_win);
	display_cycles(vm, vm->visu.cycles_win);
	display_lives(vm, vm->visu.lives_win);
	display_proc(vm->proc, vm, 1, vm->visu.proc_win);
	display_players(vm, vm->visu.players_win);
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
		/*vm->memory[0].value = (t_byte) 42;*/
		/*wclear(vm->visu.mem_win);*/
		/*display_visu(vm);*/
		/*wrefresh(vm->visu.mem_win);*/
		/*getch();*/
	}
}
