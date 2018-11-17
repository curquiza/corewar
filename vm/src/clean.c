#include "vm.h"

void	clean_all(void)
{
	int		i;

	i = 0;
	while (i < g_vm->players_number)
	{
		ft_strdel(&g_vm->player[i].prog);
		i++;
	}
}
