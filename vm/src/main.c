#include "vm.h"

t_vm *g_vm = NULL;

void	print_player(t_player *p)
{
	ft_printf("Player num %d (%#0x)\n", p->num, ~p->num);
	ft_printf("header :\n");
	ft_printf("-> magic = %#0x\n", p->header.magic);
	ft_printf("-> name = %s\n", p->header.prog_name);
	ft_printf("-> size = %d\n", p->header.prog_size);
	ft_printf("-> comment = %s\n", p->header.comment);
}

void	print_vm(t_vm *vm)
{
	int		i;

	ft_printf("VM :\n");
	ft_printf("Player number = %d\n", vm->total_players);
	ft_printf("flag = %b\n", vm->flag);
	ft_printf("Dump cycles = %d\n", vm->dump_cycle);
	ft_printf("----------------------\n");
	ft_printf("PLAYERS :\n");
	i = 0;
	while (i < vm->total_players)
	{
		print_player(&vm->player[i]);
		i++;
		ft_printf("---\n");
	}
	ft_printf("----------------------\n");
}

void	print_processus(t_vm *vm)
{
	t_processus	*proc;

	proc = vm->proc;
	while (proc)
	{
		ft_printf("index = %d\n", proc->index);
		ft_printf("cycles = %d\n", proc->cycles);
		ft_printf("opcode = 0x%0.2x\n", proc->opcode);
		ft_printf("live = %d\n", proc->live);
		ft_printf("---\n");
		proc = proc->next;
	}
}

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

void		manage_verification(t_vm *vm)
{
	ft_printf("Reseting current_cycles : %d -> %d\n", vm->current_cycles, 0);
	vm->current_cycles = 0;
	if (vm->lives < NBR_LIVE)
	{
		ft_printf("Total lives (%d) are fewer than NBR_LINE (%d)\n", vm->lives, NBR_LIVE);
		ft_printf("Incrementing verif : %d -> %d\n", vm->verif, vm->verif + 1);
		vm->verif += 1;
		if (vm->verif >= MAX_CHECKS)
		{
			ft_printf("Nb of verif (%d) reaches the maximum (%d)\n", vm->verif, MAX_CHECKS);
			ft_printf("Decrementing cycles_to_die : %d -> %d\n", vm->cycles_to_die, vm->cycles_to_die - CYCLE_DELTA);
			vm->cycles_to_die -= CYCLE_DELTA;
			ft_printf("Reseting verif : %d -> %d\n", vm->verif, 0);
			vm->verif = 0;
		}
	}
	else
	{
		ft_printf("Decrementing cycles_to_die : %d -> %d\n", vm->cycles_to_die, vm->cycles_to_die - CYCLE_DELTA);
		vm->cycles_to_die -= CYCLE_DELTA;
		ft_printf("Reseting verif : %d -> %d\n", vm->verif, 0);
		vm->verif = 0;
		ft_printf("Reseting lives : %d -> %d\n", vm->lives, 0);
		vm->lives = 0;
	}
}

void		supp_processus(t_processus **proc, t_vm *vm)
{
	t_processus	*supp;

	ft_printf("+");
	if ((*proc)->next == NULL)
		ft_printf("\n");
	supp = *proc;
	*proc = (*proc)->next;
	ft_bzero(supp, sizeof(*supp));
	free(supp);
	vm->total_proc -= 1;
}

void		kill_all_dead_processus(t_processus **proc, t_vm *vm)
{
	t_processus	*current;

	if (!proc || !*proc)
		return ;
	current = *proc;
	while (current->next)
	{
		if (current->next->live == FALSE)
			supp_processus(&current->next, vm);
	}
	if (*proc)
	{
		if ((*proc)->live == FALSE)
			supp_processus(proc, vm);
	}
}

void		reset_all_processus_live(t_processus *proc)
{
	while (proc)
	{
		proc->live = FALSE;
		proc = proc->next;
	}
}

void		execute_all_proc(t_vm *vm)
{
	(void)vm;
}

void		play_one_cycle(t_vm *vm)
{
	if (vm->cycles_to_die <= 0)
	{
		ft_printf("Cycles to die reaches 0. Gonna stop the game...\n");
		vm->play = FALSE;
	}
	else
	{
		vm->total_cycles += 1;
		vm->current_cycles += 1;
		ft_printf("execute_all_proc, cycle %d\n", vm->current_cycles);
		execute_all_proc(vm);
		if (vm->current_cycles == vm->cycles_to_die)
		{
			ft_printf("Cycles to die (%d) reached.\n", vm->cycles_to_die);
			ft_printf("Killing all dead processus : ");
			kill_all_dead_processus(&vm->proc, vm);
			ft_printf("Reseting all processus lives...\n");
			reset_all_processus_live(vm->proc);
			ft_printf("Managing verifications...\n");
			manage_verification(vm);
			if (vm->proc == NULL)
			{
				ft_printf("No remaining processus. Gonna stop the game...\n");
				vm->play = FALSE;
			}
		}
		//dump if -dump flag
	}
}

void		end_of_game(t_vm *vm)
{
	// TODO : manage visu
	g_vm->visu.enabled ? endwin() : 0;
	if (vm->last_live_player == -1)
		ft_printf("Nobody won !\n");
	else
		ft_printf("Player %d won !\n", vm->last_live_player);
	ft_printf("End of game. Thanks for watching 😎\n");
}

void		launch_corewar(t_vm *vm)
{
	vm->proc->live = TRUE; //DEBUG
	while (vm->play)
	{
		vm->visu.enabled ? getkey(vm) : 0;
		if (vm->visu.enabled == FALSE
			|| (vm->visu.enabled && vm->visu.pause == FALSE)
			|| (vm->visu.enabled && vm->visu.next_step))
		{
			play_one_cycle(vm);
			vm->visu.next_step = FALSE;
		}
		vm->visu.enabled == TRUE ? display_visu(vm) : 0;
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
