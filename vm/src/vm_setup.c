#include "vm.h"

void	fill_all_prog_in_memory(t_vm *vm)
{
	int		i;
	int		index;
	t_player	player;

	i = 0;
	while (i < vm->players_number)
	{
		index = MEM_SIZE * i / vm->players_number;
		player = vm->player[i];
		ft_memcpy(vm->memory + index, player.prog, player.header.prog_size);
		i++;
	}
}

void	vm_setup(t_vm *vm)
{
	fill_all_prog_in_memory(vm);
}
