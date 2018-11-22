#include "vm.h"

static bool	num_available(int num, t_vm *vm)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->player[i].num == num)
			return (false);
		i++;
	}
	return (true);
}

static int		generate_player_num(t_vm *vm)
{
	int		num;

	num = 1;
	while (num_available(num, vm) == false)
		num++;
	return (num);
}

t_ex_ret	parsing(int argc, char **argv, t_vm *vm)
{
	int		i;

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
	return (SUCCESS);
}
