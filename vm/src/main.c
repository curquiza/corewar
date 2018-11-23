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

int		bytes_per_line(t_vm *vm)
{
	if (flag_is_applied(ZAZ_FLAG, vm) == TRUE)
		return (BYTES_PER_LINE_ZAZ);
	return (BYTES_PER_LINE);
}

void	handle_newline(int i, t_vm *vm)
{
	int		b_per_line;

	b_per_line = i % bytes_per_line(vm);
	if (b_per_line == bytes_per_line(vm) - 1)
		ft_putchar('\n');
	else
		ft_putchar(' ');
}

void	print_mem_addr(int i, t_vm *vm)
{
	if (i % bytes_per_line(vm) == 0)
		ft_printf("0x%0.4x : ", i);
}

void	print_memory(t_vm *vm)
{
	int			i;
	t_memcase	*memory;

	memory = vm->memory;
	i = 0;
	while (i < MEM_SIZE)
	{
		print_mem_addr(i, vm);
		if (flag_is_applied(ZAZ_FLAG, vm) == TRUE)
			ft_printf("%0.2x", (t_byte) memory[i].value);
		else
			ft_printf("%s%0.2x%s", memory[i].color, (t_byte) memory[i].value,
						DEF);
		handle_newline(i, vm);
		i++;
	}
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
	if (PROG_NAME_LENGTH % 4 != 0 || PROG_NAME_LENGTH <= 0
		|| COMMENT_LENGTH % 4 != 0 || COMMENT_LENGTH <= 0
		|| MAX_PLAYERS > 4 || MAX_PLAYERS < 1
		|| MEM_SIZE < 1024 || MEM_SIZE >= 0xffff
		|| IDX_MOD != MEM_SIZE / 8
		|| CHAMP_MAX_SIZE != MEM_SIZE / 6)
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
		clean_all();
		exit(FAILURE);
	}
	vm_setup(&vm);
	/*print_vm(&vm);*/
	/*print_memory(&vm);*/
	/*print_processus(&vm);*/
	clean_all();
	return (SUCCESS);
}
