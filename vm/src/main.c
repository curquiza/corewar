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
	ft_printf("Player number = %d\n", vm->players_number);
	ft_printf("flag = %b\n", vm->flag);
	ft_printf("Dump cycles = %d\n", vm->dump_cycle);
	ft_printf("----------------------\n");
	ft_printf("PLAYERS :\n");
	i = 0;
	while (i < vm->players_number)
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

int	main (int argc, char **argv)
{
	t_vm	vm;

	g_vm = &vm;
	ft_bzero(&vm, sizeof(vm));
	if (init_check() == FAILURE)
		exit(FAILURE);
	if (argc <= 1)
		return (usage_ret_err());
	if (parsing(argc, argv, &vm) == FAILURE)
	{
		/*print_vm(&vm);*/
		clean_all();
		exit(FAILURE);
	}
	vm_setup(&vm);
	/*print_vm(&vm);*/
	/*dump_memory(&vm);*/
	/*print_processus(&vm);*/
	clean_all();
	return (SUCCESS);
}
