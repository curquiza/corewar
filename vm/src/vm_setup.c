#include "vm.h"

static int	get_beginning_index(int num, t_vm *vm)
{
	return (MEM_SIZE * num / vm->players_number);
}

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
		index = get_beginning_index(i, vm);
		fill_memory(index, &vm->player[i], vm, i);
		i++;
	}
}

static t_processus	*new_processus(int index)
{
	t_processus		*new;

	if (!(new = ft_memalloc(sizeof(*new))))
		exit_malloc_err();
	new->index = index;
	return (new);
}

static void	add_processus(t_processus **alst, t_processus *new)
{
	if (!alst)
		return ;
	else if (!*alst)
		*alst = new;
	else
	{
		new->next = *alst;
		*alst = new;
	}
}

static void	create_all_first_processus(t_vm *vm)
{
	int		i;
	int		index;

	i = vm->players_number;
	while (i >= 0)
	{
		index = get_beginning_index(i, vm);
		add_processus(&vm->proc, new_processus(index));
		i--;
	}
}

void	vm_setup(t_vm *vm)
{
	fill_all_prog_in_memory(vm);
	create_all_first_processus(vm);
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->last_live_player_id = -1;
}
