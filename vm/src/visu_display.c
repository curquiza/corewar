#include "vm.h"

static int	get_attr(t_memcase *memory)
{
	if (memory->proc == TRUE)
		return (COLOR_PAIR(memory->color_visu) | A_STANDOUT);
	return (COLOR_PAIR(memory->color_visu));
}

static int	bytes_per_line(t_vm *vm)
{
	if (vm->visu.type == MINI_V)
		return (BYTES_PER_LINE_32);
	return (BYTES_PER_LINE_64);
}

static void	print_mem_addr_visu(int i, t_vm *vm, WINDOW *win)
{
	if (i % bytes_per_line(vm) == 0)
		wprintw(win, "0x%0.4x |   ", i);
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
	mvwprintw(stdscr, MINI_MEM_WIN_Y + 1, 2, "MEMORY PART %d/3", part);
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
	if (vm->last_live_player == -1)
		mvwprintw(win, 6, 2, "%-15s%s", "Last player", "None");
	else
		mvwprintw(win, 6, 2, "%-15s%d", "Last player", vm->last_live_player);
	mvwprintw(win, 8, 2, "%-15s%d", "Min lives", NBR_LIVE);
	mvwprintw(win, 9, 2, "%-15s%d", "Max checks", MAX_CHECKS);
}

static void	display_proc(t_vm *vm, int proc_id, WINDOW *win)
{
	int		i;
	t_processus	*proc;

	if (vm->proc == NULL)
		return ;
	proc = vm->proc;
	i = 1;
	while (i != proc_id)
	{
		proc = proc->next;
		i++;
	}
	box(win, ACS_VLINE, ACS_HLINE);
	mvwprintw(win, 1, 2, "%-15s%d/%d", "PROCESSUS", proc_id, vm->total_proc);
	mvwprintw(win, 3, 2, "%-15s%d", "PC", proc->pc);
	mvwprintw(win, 4, 2, "%-15s%d", "Carry", proc->carry);
	mvwprintw(win, 5, 2, "%-15s%s", "Alive ?", proc->live ? "Yes" : "No");
	if (proc->current_op)
		mvwprintw(win, 7, 2, "%-15s%s", "Op", proc->current_op->name);
	else
		mvwprintw(win, 7, 2, "%-15s%s", "Op", "None");
	mvwprintw(win, 8, 2, "%-15s%d", "Cycles", proc->cycles);
	i = 0;
	while (i < REG_NUMBER)
	{
		mvwprintw(win, 10 + i, 2, "R%-9.2d 0x%.8x", i + 1, proc->reg[i]);
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
		/*mvwprintw(wins[i], 1, 2, "PLAYER %d", vm->player[i].num);*/
		mvwprintw(wins[i], 1, 2, "PLAYER %d", i + 1);
		wattroff(wins[i], COLOR_PAIR(get_player_color(i)));
		mvwprintw(wins[i], 3, 2, "%-15s%d", "Num", vm->player[i].num);
		mvwprintw(wins[i], 4, 2, "%-15s%s", "Name", vm->player[i].header.prog_name);
		/*mvwprintw(wins[i], 4, 2, "%-15s%d", "Prog size", vm->player[i].header.prog_size);*/
		i++;
	}
}

static void	display_usage(t_vm *vm, WINDOW *win)
{
	(void)vm;
	box(win, ACS_VLINE, ACS_HLINE);
	mvwprintw(win, 1, 2, "USAGE");
	mvwprintw(win, 3, 2, "%-10s%16s", "<space>", "start/stop");
	mvwprintw(win, 4, 2, "%-10s%16s", "n", "next step");
	mvwprintw(win, 5, 2, "%-10s%16s", "m", "next memory part");
	mvwprintw(win, 6, 2, "%-10s%16s", "p", "next processus");
}

static void	load_proc_display(t_vm *vm)
{
	t_processus *proc;

	proc = vm->proc;
	while (proc)
	{
		vm->memory[proc->pc].proc = TRUE;
		proc = proc->next;
	}
}

static void	rm_proc_display(t_vm *vm)
{
	t_processus *proc;

	proc = vm->proc;
	while (proc)
	{
		vm->memory[proc->pc].proc = FALSE;
		proc = proc->next;
	}
}

static void		refresh_all(t_vm *vm)
{
	int		i;

	wrefresh(vm->visu.mem_win);
	wrefresh(vm->visu.cycles_win);
	wrefresh(vm->visu.lives_win);
	wrefresh(vm->visu.proc_win);
	wrefresh(vm->visu.usage_win);
	i = 0;
	while (i < vm->total_players)
	{
		wrefresh(vm->visu.players_win[i]);
		i++;
	}
}

void	display_visu(t_vm *vm)
{

	erase();
	load_proc_display(vm);
	if (vm->visu.type == MINI_V)
		dump_memory_mini_visu_part(vm, vm->visu.mem_win, vm->visu.mem_part);
	else
		dump_memory_visu(vm, vm->visu.mem_win);
	rm_proc_display(vm);
	display_cycles(vm, vm->visu.cycles_win);
	display_lives(vm, vm->visu.lives_win);
	display_proc(vm, vm->visu.proc_id, vm->visu.proc_win);
	display_players(vm, vm->visu.players_win);
	display_usage(vm, vm->visu.usage_win);
	refresh_all(vm);
}
