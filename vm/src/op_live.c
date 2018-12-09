#include "vm.h"

static t_player	*get_player(int num, t_player *players, int total_players)
{
	int		i;

	i = 0;
	while (i < total_players)
	{
		if (~players[i].num == num)
			return (&players[i]);
		i++;
	}
	return (NULL);
}

void	op_live(t_vm *vm, t_processus *proc, t_param *params)
{
	t_player		*player;

	print_str("\tExecuting LIVE\n", ALL, vm);
	player = get_player(params[0].value, vm->player, vm->total_players);
	if (player)
	{
		ft_dprintf(vm->trace_fd, "Player %d (%s) is alive\n",
					player->num, player->header.prog_name);
		vm->last_live_player = player->num;
	}
	proc->live = TRUE;
	vm->lives += 1;
}
