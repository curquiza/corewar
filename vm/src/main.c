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

void	print_memory(t_memcase *memory)
{
	int		i;
	int		line;

	i = 0;
	line = 1;
	while (i < MEM_SIZE)
	{
		ft_printf("%s%0.2x%s", memory[i].color, (t_byte) memory[i].value, DEF);
		if (line == 32)
		{
			ft_putchar('\n');
			line = 1;
		}
		else
			ft_putchar(' ');
		line++;
		i++;
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
	print_memory(vm.memory);
	/*print_vm(&vm);*/
	clean_all();
	return (SUCCESS);
}
