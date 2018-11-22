#include "vm.h"

void	fill_memory(int index, t_player *player, t_vm *vm, int player_num)
{
	unsigned int	i;

	i = 0;
	while (i < player->header.prog_size)
	{
		if (i + index >= MEM_SIZE)
			break;
		vm->memory[index + i].value = player->prog[i];
		if (player_num == 0)
			ft_strcpy(vm->memory[index + i].color, CYAN);
		else if (player_num == 1)
			ft_strcpy(vm->memory[index + i].color, PINK);
		else if (player_num == 2)
			ft_strcpy(vm->memory[index + i].color, GREEN);
		else
			ft_strcpy(vm->memory[index + i].color, YELLOW);
		i++;
	}
}

void	fill_all_prog_in_memory(t_vm *vm)
{
	int		i;
	int		index;

	i = 0;
	while (i < vm->players_number)
	{
		index = MEM_SIZE * i / vm->players_number;
		fill_memory(index, &vm->player[i], vm, i);
		i++;
	}
}

void	vm_setup(t_vm *vm)
{
	fill_all_prog_in_memory(vm);
}
