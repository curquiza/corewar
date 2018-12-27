#include "vm.h"

void	display_cycles(t_vm *vm, WINDOW *win)
{
	box(win, ACS_VLINE, ACS_HLINE);
	mvwprintw(win, 1, 9, "CYCLES");
	mvwprintw(win, 2, 2, "---------------------");
	mvwprintw(win, 4, 2, "%-15s%6d", "Total", vm->total_cycles);
	mvwprintw(win, 5, 2, "%-15s%6d", "Current", vm->current_cycles);
	mvwprintw(win, 7, 2, "%-15s%6d", "Cycle to die", vm->cycles_to_die);
	mvwprintw(win, 8, 2, "%-15s%6d", "Cycle delta", CYCLE_DELTA);
}
