#include "vm.h"

static int	get_beginning_index(int num, t_vm *vm)
{
	return (MEM_SIZE * num / vm->total_players);
}

static void	fill_player_color(int player_id, t_memcase *memcase)
{

	if (player_id == 0)
	{
		ft_strcpy(memcase->color, CYAN);
		memcase->color_visu = CYAN_PAIR;
	}
	else if (player_id == 1)
	{
		ft_strcpy(memcase->color, PINK);
		memcase->color_visu = PINK_PAIR;
	}
	else if (player_id == 2)
	{
		ft_strcpy(memcase->color, GREEN);
		memcase->color_visu = GREEN_PAIR;
	}
	else
	{
		ft_strcpy(memcase->color, YELLOW);
		memcase->color_visu = YELLOW_PAIR;
	}
}

static void	fill_memory(int index, t_player *player, t_vm *vm, int player_id)
{
	unsigned int	i;

	i = 0;
	while (i < player->header.prog_size)
	{
		if (i + index >= MEM_SIZE)
			break;
		vm->memory[index + i].value = player->prog[i];
		fill_player_color(player_id, &vm->memory[index + i]);
		i++;
	}
}

static void	fill_all_prog_in_memory(t_vm *vm)
{
	int		i;
	int		index;

	i = 0;
	while (i < vm->total_players)
	{
		index = get_beginning_index(i, vm);
		fill_memory(index, &vm->player[i], vm, i);
		i++;
	}
}

static t_processus	*new_processus(int index, t_vm *vm)
{
	t_processus		*new;

	if (!(new = ft_memalloc(sizeof(*new))))
		exit_malloc_err();
	new->pc = index;
	vm->memory[index].proc = TRUE;
	vm->total_proc += 1;
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

	i = 0;
	while (i < vm->total_players)
	{
		index = get_beginning_index(i, vm);
		add_processus(&vm->proc, new_processus(index, vm));
		vm->proc->reg[0] = ~vm->player[i].num;
		i++;
	}
}

void		vm_setup(t_vm *vm)
{
	fill_all_prog_in_memory(vm);
	create_all_first_processus(vm);
	vm->run = ON;
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->last_live_player = -1;
	vm->trace_fd = STDOUT_FILENO;
	if (flag_is_applied(VISU_FLAG, vm) == TRUE)
	{
		if ((vm->trace_fd
			= open_file(TRACE_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644))
			== FAILURE)
		{
			ft_dprintf(2, "Error: %s\n", VISU_TRACE_ERR);
			vm->trace_fd = STDOUT_FILENO;
		}
		else
			start_visu(vm);
	}
	if (flag_is_applied(DUMP_FLAG, vm) == TRUE && vm->dump_cycle == 0)
	{
		dump_memory(vm);
		vm->run = vm->visu.enabled ? vm->run : BREAK;
	}
}
