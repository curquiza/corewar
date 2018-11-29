#include "vm.h"

void	clean_all(void)
{
	t_processus	*tmp;
	t_processus	*proc;

	g_vm->visu.enabled == TRUE ? endwin() : 0;
	proc = g_vm->proc;
	while (proc)
	{
		tmp = proc;
		proc = proc->next;
		free(tmp);
	}
}
