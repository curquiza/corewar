#include "vm.h"

static t_ex_ret	parse_num_flag(char **argv, int *i, t_vm *vm)
{
	int		num;

	num = 0;
	if (!argv[*i + 1] || !argv[*i + 2])
		return (ft_ret_err(PLAYER_NUM_ERR1));
	if (ft_is_int(argv[*i + 1]) == 0 || ft_atoi(argv[*i + 1]) < 0)
		return (ft_ret_err(PLAYER_NUM_ERR2));
	num = ft_atoi(argv[*i + 1]);
	if (manage_player(argv[*i + 2], vm, num) == FAILURE)
		return (FAILURE);
	*i += 2;
	return (SUCCESS);
}

static t_ex_ret	parse_dump_flag(char **argv, int *i, t_vm *vm)
{
	if (!argv[*i + 1])
		return (ft_ret_err(DUMP_CYCLE_ERR1));
	if (ft_is_int(argv[*i + 1]) == 0 || ft_atoi(argv[*i + 1]) < 0)
		return (ft_ret_err(DUMP_CYCLE_ERR2));
	vm->flag |= DUMP_FLAG;
	vm->dump_cycle = ft_atoi(argv[*i + 1]);
	*i += 1;
	return (SUCCESS);
}

static t_ex_ret parse_visu_flag(t_vm *vm)
{
	if (flag_is_applied(MINI_VISU_FLAG, vm) == TRUE)
		return (ft_ret_err(VISU_ERR));
	vm->flag |= VISU_FLAG;
	return (SUCCESS);
}

static t_ex_ret parse_mini_visu_flag(t_vm *vm)
{
	if (flag_is_applied(VISU_FLAG, vm) == TRUE)
		return (ft_ret_err(VISU_ERR));
	vm->flag |= MINI_VISU_FLAG;
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
	else if (ft_strequ(argv[*i], VISU_FLAG_STR))
		return (parse_visu_flag(vm));
	else if (ft_strequ(argv[*i], MINI_VISU_FLAG_STR))
		return (parse_mini_visu_flag(vm));
	else
		return (ft_ret_err2(argv[*i], WRONG_FLAG_ERR));
	return (SUCCESS);
}
