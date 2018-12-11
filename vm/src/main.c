#include "vm.h"

t_vm *g_vm = NULL;

/*void	print_player(t_player *p)*/
/*{*/
	/*ft_printf("Player num %d (%#0x)\n", p->num, ~p->num);*/
	/*ft_printf("header :\n");*/
	/*ft_printf("-> magic = %#0x\n", p->header.magic);*/
	/*ft_printf("-> name = %s\n", p->header.prog_name);*/
	/*ft_printf("-> size = %d\n", p->header.prog_size);*/
	/*ft_printf("-> comment = %s\n", p->header.comment);*/
/*}*/

/*void	print_vm(t_vm *vm)*/
/*{*/
	/*int		i;*/

	/*ft_printf("VM :\n");*/
	/*ft_printf("Player number = %d\n", vm->total_players);*/
	/*ft_printf("flag = %b\n", vm->flag);*/
	/*ft_printf("Dump cycles = %d\n", vm->dump_cycle);*/
	/*ft_printf("----------------------\n");*/
	/*ft_printf("PLAYERS :\n");*/
	/*i = 0;*/
	/*while (i < vm->total_players)*/
	/*{*/
		/*print_player(&vm->player[i]);*/
		/*i++;*/
		/*ft_printf("---\n");*/
	/*}*/
	/*ft_printf("----------------------\n");*/
/*}*/

/*void	print_processus(t_vm *vm)*/
/*{*/
	/*t_processus	*proc;*/

	/*proc = vm->proc;*/
	/*while (proc)*/
	/*{*/
		/*ft_printf("PC = %d\n", proc->pc);*/
		/*ft_printf("cycles = %d\n", proc->cycles);*/
		/*//ft_printf("opcode = 0x%0.2x\n", proc->opcode);*/
		/*ft_printf("live = %d\n", proc->live);*/
		/*ft_printf("---\n");*/
		/*proc = proc->next;*/
	/*}*/
/*}*/

/*void		print_g_op(void)*/
/*{*/
	/*int		i;*/

	/*i = 1;*/
	/*while (i < OP_NUMBER + 1)*/
	/*{*/
		/*ft_printf("Opcode = 0x%.2x\n", g_op[i].opcode);*/
		/*ft_printf("Name = %s\n", g_op[i].name);*/
		/*ft_printf("Param number = %d\n", g_op[i].param_nb);*/
		/*ft_printf("Param type :\n");*/
		/*ft_printf(" > %b\n", g_op[i].param_type[0]);*/
		/*ft_printf(" > %b\n", g_op[i].param_type[1]);*/
		/*ft_printf(" > %b\n", g_op[i].param_type[2]);*/
		/*ft_printf(" > %b\n", g_op[i].param_type[3]);*/
		/*ft_printf("Cycles = %d\n", g_op[i].cycles);*/
		/*ft_printf("OCP ? %d\n", g_op[i].ocp);*/
		/*ft_printf("Index ? %d\n", g_op[i].index);*/
		/*ft_printf("---------\n");*/
		/*i++;*/
	/*}*/
/*}*/

t_ex_ret	init_check(void)
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

void		play_one_cycle(t_vm *vm)
{
	vm->total_cycles += 1;
	vm->current_cycles += 1;
	print_str_int("Starting a new cycle", vm->current_cycles, FEW, vm);
	print_str("Executing all process\n", FEW, vm);
	exec_all_proc(vm);
	if (vm->current_cycles == vm->cycles_to_die)
		manage_end_of_period(vm);
	print_str("----------\n", FEW, vm);
	if (vm->current_cycles == vm->dump_cycle)
	{
		dump_memory(vm);
		vm->run = BREAK;
	}
}

static t_player	*get_player(int num, t_player *players, int total_players)
{
	int		i;

	i = 0;
	while (i < total_players)
	{
		if (players[i].num == num)
			return (&players[i]);
		i++;
	}
	return (NULL);
}

void		end_of_game(t_vm *vm)
{
	t_player	*p;

	// TODO : manage visu
	g_vm->visu.enabled ? sleep(3) : 0;
	g_vm->visu.enabled ? endwin() : 0;
	g_vm->visu.enabled ? close(vm->trace_fd) : 0;
	if (vm->run != BREAK)
	{
		if (vm->last_live_player == -1)
			ft_printf("Nobody won !\n");
		else
		{
			p = get_player(vm->last_live_player, vm->player, vm->total_players);
			ft_printf("Player %d (%s) won !\n", vm->last_live_player, p->header.prog_name);
		}
		ft_printf("End of game. Thanks for watching 😎\n");
	}
}

void		launch_corewar(t_vm *vm)
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
		vm->visu.enabled? display_visu(vm) : 0;
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
	//print_g_op();
	vm_setup(&vm);
	launch_corewar(&vm);
	clean_all();
	return (SUCCESS);
}
