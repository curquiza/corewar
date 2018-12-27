#include "vm.h"

void	display_usage(t_vm *vm, WINDOW *win)
{
	(void)vm;
	box(win, ACS_VLINE, ACS_HLINE);
	mvwprintw(win, 1, 2, "USAGE");
	mvwprintw(win, 3, 2, "%-10s%21s", "<space>", "start/stop");
	mvwprintw(win, 4, 2, "%-10s%21s", "n", "next step");
	mvwprintw(win, 5, 2, "%-10s%21s", "m", "next memory part");
	mvwprintw(win, 6, 2, "%-10s%21s", "P/p", "prev/next processus");
}
