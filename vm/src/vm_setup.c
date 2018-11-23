#include "vm.h"

static char	*get_player_color(int player_num)
{
	if (player_num == 0)
		return (CYAN);
	else if (player_num == 1)
		return (PINK);
	else if (player_num == 2)
		return (GREEN);
	else
		return (YELLOW);
}

static void	fill_memory(int index, t_player *player, t_vm *vm, int player_num)
{
	unsigned int	i;

	i = 0;
	while (i < player->header.prog_size)
	{
		if (i + index >= MEM_SIZE)
			break;
		vm->memory[index + i].value = player->prog[i];
		ft_strcpy(vm->memory[index + i].color, get_player_color(player_num));
		i++;
	}
}

static void	fill_all_prog_in_memory(t_vm *vm)
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
