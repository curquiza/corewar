#include "vm.h"

t_vm *g_vm = NULL;

static t_ex_ret	init_check(void)
{
	if (IND_SIZE != 2 || REG_SIZE != 4 || DIR_SIZE != REG_SIZE
		|| REG_CODE != 1 || DIR_CODE != 2 || IND_CODE != 3
		|| MAX_ARGS_NUMBER != 4
		|| MAX_PLAYERS > 4 || MAX_PLAYERS < 1
		|| MEM_SIZE < 1024 || MEM_SIZE >= 0xffff
		|| IDX_MOD != MEM_SIZE / 8
		|| CHAMP_MAX_SIZE != MEM_SIZE / 6
		|| REG_NUMBER != 16
		|| CYCLE_TO_DIE != 1536 || CYCLE_DELTA != 50
		|| NBR_LIVE != 21 || MAX_CHECKS != 10
		|| PROG_NAME_LENGTH % 4 != 0 || PROG_NAME_LENGTH <= 0
		|| COMMENT_LENGTH % 4 != 0 || COMMENT_LENGTH <= 0)
		return (ft_ret_err(DEFINE_ERR));
	return (SUCCESS);
}

static void		play_one_cycle(t_vm *vm)
{
	vm->total_cycles += 1;
	vm->current_cycles += 1;
	print_str("Starting a new cycle : ", FEW, vm);
	print_compare_intvar(vm->current_cycles, vm->total_cycles, FEW, vm);
	print_str("Executing all process\n", FEW, vm);
	exec_all_proc(vm, vm->proc);
	if (vm->current_cycles == vm->cycles_to_die)
		manage_end_of_period(vm);
	print_str("----------\n", FEW, vm);
}

static void		launch_corewar(t_vm *vm)
{
	while (vm->run == ON)
	{
		vm->visu.enabled ? getkey(vm) : 0;
		if (vm->visu.enabled == FALSE
			|| (vm->visu.enabled && vm->visu.pause == FALSE)
			|| (vm->visu.enabled && vm->visu.next_step))
		{
			play_one_cycle(vm);
			vm->visu.next_step = FALSE;
		}
		vm->visu.enabled ? display_visu(vm) : 0;
		if (flag_is_applied(DUMP_FLAG, vm) == TRUE
			&&	vm->total_cycles == vm->dump_cycle)
		{
			dump_memory(vm);
			vm->run = vm->visu.enabled ? vm->run : BREAK;
		}
	}
	end_of_game(vm);
}

int	main (int argc, char **argv)
{
	t_vm	vm;

	g_vm = &vm;
	ft_bzero(&vm, sizeof(vm));
	if (init_check() == FAILURE)
		exit(FAILURE);
	if (parsing(argc, argv, &vm) == FAILURE)
	{
		clean_all();
		exit(FAILURE);
	}
	vm_setup(&vm);
	launch_corewar(&vm);
	clean_all();
	return (SUCCESS);
}
