#include "vm.h"

/*t_bool		kbhit(void)*/
/*{*/
	/*int c;*/

	/*c = getch();*/
	/*if (c != ERR)*/
	/*{*/
		/*ungetch(c);*/
		/*return (TRUE);*/
	/*}*/
	/*else*/
		/*return (FALSE);*/
/*}*/

void	getkey(t_vm *vm)
{
	char	c;

	c = getch();
	if (c == 'n')
		vm->visu.next_step = TRUE;
	else if (c == ' ')
	{
		if (vm->visu.pause)
		{
			vm->visu.pause = FALSE;
			nodelay(stdscr, TRUE);
		}
		else
		{
			vm->visu.pause = TRUE;
			nodelay(stdscr, FALSE);
		}
	}
	else if (c == 'm' && vm->visu.type == MINI_V)
	{
		wclear(vm->visu.mem_win);
		vm->visu.mem_part = vm->visu.mem_part % 3 + 1;
	}
	else if (c == 'p')
	{
		wclear(vm->visu.proc_win);
		vm->visu.proc_id = vm->visu.proc_id % vm->total_proc + 1;
	}
}
