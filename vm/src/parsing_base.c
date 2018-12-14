#include "vm.h"

static t_bool	num_available(int num, t_vm *vm)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->player[i].num == num)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int		generate_player_num(t_vm *vm)
{
	int		num;

	num = 0;
	while (num_available(num, vm) == FALSE)
		num++;
	return (num);
}

static void	init_player_num(t_player *players)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		players[i].num = -1;
		i++;
	}
}

t_ex_ret	parsing(int argc, char **argv, t_vm *vm)
{
	int		i;

	if (argc <= 1)
		return (usage_ret_err());
	init_player_num(vm->player);
	i = 1;
	while (i < argc)
	{
		if (argv[i] && ft_strlen(argv[i]) > 1 && argv[i][0] == '-')
		{
			if (manage_flag(argv, &i, vm) == FAILURE)
				return (FAILURE);
		}
		else if (argv[i])
		{
			if (manage_player(argv[i], vm, generate_player_num(vm))
				== FAILURE)
				return (FAILURE);
		}
		i++;
	}
	if (vm->total_players == 0)
		return (usage_ret_err());
	return (SUCCESS);
}