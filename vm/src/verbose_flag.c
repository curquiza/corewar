#include "vm.h"

void	print_str(char *s, t_verbose type, t_vm *vm)
{
	int		fd;

	if ((vm->verbose == NONE && type != NONE)
		|| (vm->verbose == FEW && type <= FEW))
		return ;
	fd = vm->visu.enabled ? vm->visu.trace_fd : STDOUT_FILENO;
	ft_dprintf(fd, "%s", s);
}

void	print_upd_intvar(int v1, int v2, t_verbose type, t_vm *vm)
{
	int		fd;

	if ((vm->verbose == NONE && type != NONE)
		|| (vm->verbose == FEW && type <= FEW))
		return ;
	fd = vm->visu.enabled ? vm->visu.trace_fd : STDOUT_FILENO;
	ft_dprintf(fd, "%d -> %d\n", v1, v2);
}

void	print_compare_intvar(int v1, int v2, t_verbose type, t_vm *vm)
{
	int		fd;

	if ((vm->verbose == NONE && type != NONE)
		|| (vm->verbose == FEW && type <= FEW))
		return ;
	fd = vm->visu.enabled ? vm->visu.trace_fd : STDOUT_FILENO;
	ft_dprintf(fd, "%d // %d\n", v1, v2);
}
