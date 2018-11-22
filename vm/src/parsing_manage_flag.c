#include "vm.h"

static t_ex_ret	parse_num_flag(char **argv, int *i, t_vm *vm)
{
	int		num;

	num = 0;
	if (!argv[*i + 1] || ft_is_int(argv[*i + 1]) == 0
		|| ft_atoi(argv[*i + 1]) < 0)
		return (player_num_err());
	num = ft_atoi(argv[*i + 1]);
	if (manage_player(argv[*i + 2], vm, num) == FAILURE)
		return (FAILURE);
	*i += 2;
	return (SUCCESS);
}

static t_ex_ret	parse_dump_flag(char **argv, int *i, t_vm *vm)
{
	if (!argv[*i + 1] || ft_is_int(argv[*i + 1]) == 0
		|| ft_atoi(argv[*i + 1]) < 0)
		return (dump_cycle_err());
	vm->flag |= DUMP_FLAG;
	vm->dump_cycle = ft_atoi(argv[*i + 1]);
	*i += 1;
	return (SUCCESS);
}

t_ex_ret			manage_flag(char **argv, int *i, t_vm *vm)
{
	if (ft_strequ(argv[*i], NUM_FLAG_STR))
		return (parse_num_flag(argv, i, vm));
	else if (ft_strequ(argv[*i], DUMP_FLAG_STR))
		return (parse_dump_flag(argv, i, vm));
	else if (ft_strequ(argv[*i], ZAZ_FLAG_STR))
		vm->flag |= ZAZ_FLAG;
	else
		return (wrong_flag_err(argv[*i]));
	return (SUCCESS);
}
