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

bool	num_available(int num, t_vm *vm)
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

int		generate_player_num(t_vm *vm)
{
	int		num;

	num = 1;
	while (num_available(num, vm) == false)
		num++;
	return (num);
}

t_exit	max_player_err(void)
{
	ft_dprintf(2, MAX_PLAYER_ERR);
	return (EXIT_FAILURE);
}

t_exit	manage_player(char *filename, t_vm *vm, int num)
{
	t_player	*player;

	if (vm->players_number + 1 > MAX_PLAYERS)
		return (max_player_err());
	vm->players_number += 1;
	player = &vm->player[vm->players_number - 1];
	player->num = num;
	if (parse_player(filename, player) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	print_player(player);
	return (EXIT_SUCCESS);
}

t_exit	wrong_flag_err(char *s)
{
	ft_dprintf(2, "Error: %s: %s", s, WRONG_FLAG_ERR);
	return (EXIT_FAILURE);
}

t_exit	player_num_err(void)
{
	ft_dprintf(2, PLAYER_NUM_ERR);
	return (EXIT_FAILURE);
}

t_exit	dump_cycle_err(void)
{
	ft_dprintf(2, DUMP_CYCLE_ERR);
	return (EXIT_FAILURE);
}

t_exit	manage_flags(char **argv, int *i, t_vm *vm)
{
	int		num;

	if (ft_strequ(argv[*i], NUM_FLAG_STR))
	{
		num = 0;
		if (!argv[*i + 1] || ft_is_int(argv[*i + 1]) == 0)
			return (player_num_err());
		num = ft_atoi(argv[*i + 1]);
		if (manage_player(argv[*i + 2], vm, num) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		/*print_player(&vm->player[vm->players_number - 1]); //DEBUG*/
		*i += 2;
	}
	else if (ft_strequ(argv[*i], DUMP_FLAG_STR))
	{
		if (!argv[*i + 1] || ft_is_int(argv[*i + 1]) == 0)
			return (dump_cycle_err());
		vm->flag |= DUMP_FLAG;
		vm->dump_cycle = ft_atoi(argv[*i + 1]);
		*i += 1;
	}
	else if (ft_strequ(argv[*i], ZAZ_FLAG_STR))
		vm->flag |= ZAZ_FLAG;
	else
		return (wrong_flag_err(argv[*i]));
	return (EXIT_SUCCESS);
}

t_exit	parsing(int argc, char **argv, t_vm *vm)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (argv[i] && ft_strlen(argv[i]) > 1 && argv[i][0] == '-')
		{
			/*ft_printf("FLAG\n"); //DEBUG*/
			if (manage_flags(argv, &i, vm) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (argv[i])
		{
			/*ft_printf("PLAYER\n"); //DEBUG*/
			if (manage_player(argv[i], vm, generate_player_num(vm))
				== EXIT_FAILURE)
				return (EXIT_FAILURE);
			/*print_player(&vm->player[vm->players_number - 1]); //DEBUG*/
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
