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

t_exit	manage_player(char *filename, t_vm *vm)
{
	t_player	*player;

	player = &vm->player[vm->players_number - 1];
	player->num = vm->players_number;
	if (parse_player(filename, player) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_exit	parsing(int argc, char **argv, t_vm *vm)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (argv[i] && ft_strlen(argv[i]) > 1 && argv[i][0] == '-')
			/*manage_option(argv[i], vm);*/
			ft_printf("OPTION\n"); //DEBUG
		else if (argv[i])
		{
			ft_printf("PLAYER\n"); //DEBUG
			vm->players_number += 1;
			if (vm->players_number > MAX_PLAYERS)
			{
				ft_dprintf(2, MAX_PLAYER_ERR);
				return (EXIT_FAILURE);
			}
			if (manage_player(argv[i], vm) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			print_player(&vm->player[vm->players_number - 1]); //DEBUG
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

t_exit	init_check(void)
{
	if (PROG_NAME_LENGTH % 4 != 0 || PROG_NAME_LENGTH <= 0
		|| COMMENT_LENGTH % 4 != 0 || COMMENT_LENGTH <= 0)
	{
		ft_dprintf(2, DEFINE_ERR);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main (int argc, char **argv)
{
	t_vm	vm;

	g_vm = &vm;
	ft_bzero(&vm, sizeof(vm));
	if (init_check() == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	if (argc <= 1)
	{
		print_usage();
		exit(EXIT_FAILURE);
	}
	if (parsing(argc, argv, &vm) == EXIT_FAILURE)
	{
		clean_all();
		exit(EXIT_FAILURE);
	}
	clean_all();
	return (EXIT_SUCCESS);
}
