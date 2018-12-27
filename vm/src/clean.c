#include "vm.h"

void	clean_all(void)
{
	t_processus	*tmp;
	t_processus	*proc;

	proc = g_vm->proc;
	while (proc)
	{
		tmp = proc;
		proc = proc->next;
		free(tmp);
	}
}
