#include "vm.h"

static t_bool	num_available(int num, t_vm *vm)
{
	int		i;

	i = 0;
	while (i < vm->total_players)
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

static t_bool	check_double_num(int current_player_id, t_vm *vm)
{
	int		i;

	i = 0;
	while (i < vm->total_players)
	{
		if (i != current_player_id
			&& vm->player[i].num == vm->player[current_player_id].num)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static t_ex_ret	manage_players_numbers(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < vm->total_players)
	{
		if (vm->player[i].num == -1)
			vm->player[i].num = generate_player_num(vm);
		else
		{
			if (check_double_num(i, vm) == FALSE)
				return (ft_ret_err(PLAYER_NUM_ERR3));
		}
		i++;
	}
	return (SUCCESS);
}

t_ex_ret	parsing(int argc, char **argv, t_vm *vm)
{
	int		i;

	if (argc <= 1)
		return (usage_ret_err());
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
			if (manage_player(argv[i], vm, -1)
				== FAILURE)
				return (FAILURE);
		}
		i++;
	}
	if (vm->total_players == 0)
		return (usage_ret_err());
	return (manage_players_numbers(vm));
}
