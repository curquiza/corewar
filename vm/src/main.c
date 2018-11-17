#include "vm.h"

t_vm *g_vm = NULL;

uint32_t	str_to_uint32(char *str)
{
	uint32_t		rslt;

	rslt = 0;
	rslt = (rslt | (t_byte)str[0]) << 8;
	rslt = (rslt | (t_byte)str[1]) << 8;
	rslt = (rslt | (t_byte)str[2]) << 8;
	rslt |= (t_byte)str[3];
	return (rslt);
}

t_exit	read_magic(char *filename, int fd, t_header *header)
{
	char	buff[4];
	int		read_ret;

	read_ret = read(fd, buff, 4);
	if (read_ret == -1)
		return (read_error(filename));
	if (read_ret != 4 || COREWAR_EXEC_MAGIC != str_to_uint32(buff))
	{
		ft_dprintf(2, HEADER_ERR);
		return (EXIT_FAILURE);
	}
	/*printf("real magic = %0x\n", COREWAR_EXEC_MAGIC); //DEBUG*/
	/*printf("my magic = %0x\n", str_to_uint32(buff));   //DEBUG*/
	header->magic = str_to_uint32(buff);
	return (EXIT_SUCCESS);
}

t_exit	read_name(char *filename, int fd, t_header *header)
{
	char	buff[PROG_NAME_LENGTH];
	int		read_ret;

	read_ret = read(fd, buff, PROG_NAME_LENGTH);
	if (read_ret == -1)
		return (read_error(filename));
	if (read_ret != PROG_NAME_LENGTH)
	{
		ft_dprintf(2, HEADER_ERR);
		return (EXIT_FAILURE);
	}
	/*ft_bzero(header->prog_name, PROG_NAME_LENGTH + 1);*/
	ft_memcpy(header->prog_name, buff, PROG_NAME_LENGTH);
	return (EXIT_SUCCESS);
}

t_exit	read_zero_block(char *filename, int fd)
{
	char	buff[4];
	int		read_ret;

	read_ret = read(fd, buff, 4);
	if (read_ret == -1)
		return (read_error(filename));
	if (read_ret != 4 || str_to_uint32(buff) != 0)
	{
		ft_dprintf(2, HEADER_ERR);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_exit	read_prog_size(char *filename, int fd, t_header *header)
{
	char	buff[4];
	int		read_ret;

	read_ret = read(fd, buff, 4);
	if (read_ret == -1)
		return (read_error(filename));
	if (read_ret != 4)
	{
		ft_dprintf(2, HEADER_ERR);
		return (EXIT_FAILURE);
	}
	header->prog_size = str_to_uint32(buff);
	return (EXIT_SUCCESS);
}

t_exit	read_comment(char *filename, int fd, t_header *header)
{
	char	buff[COMMENT_LENGTH];
	int		read_ret;

	read_ret = read(fd, buff, COMMENT_LENGTH);
	if (read_ret == -1)
		return (read_error(filename));
	if (read_ret != COMMENT_LENGTH)
	{
		ft_dprintf(2, HEADER_ERR);
		return (EXIT_FAILURE);
	}
	ft_bzero(header->comment, COMMENT_LENGTH + 1);
	ft_memcpy(header->comment, buff, COMMENT_LENGTH);
	return (EXIT_SUCCESS);
}


/*
** Read of prog_size +1 -> to check if the prog is not too big.
*/
t_exit	read_prog(char *filename, int fd, t_player *player)
{
	char	*buff;
	int		read_ret;

	if (!(buff = ft_memalloc(sizeof(char) * (player->header.prog_size + 1))))
		return (EXIT_FAILURE);
	read_ret = read(fd, buff, player->header.prog_size + 1);
	if (read_ret == -1)
	{
		ft_strdel(&buff);
		return (read_error(filename));
	}
	if ((unsigned int)read_ret != player->header.prog_size)
	{
		ft_strdel(&buff);
		ft_dprintf(2, PROG_SIZE_ERR);
		return (EXIT_FAILURE);
	}
	if (!(player->prog = ft_strdup(buff)))
	{
		ft_strdel(&buff);
		return (EXIT_FAILURE);
	}
	ft_strdel(&buff);
	return (EXIT_SUCCESS);
}

t_exit	parse_player(char *filename, t_player *player, int num)
{
	int		fd;
	t_header	*player_header;

	player_header = &player->header;
	player->num = num;
	if ((fd = open_file(filename)) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (read_magic(filename, fd, player_header) == EXIT_FAILURE
			|| read_name(filename, fd, player_header) == EXIT_FAILURE
			|| read_zero_block(filename, fd) == EXIT_FAILURE
			|| read_prog_size(filename, fd, player_header) == EXIT_FAILURE
			|| read_comment(filename, fd, player_header) == EXIT_FAILURE
			|| read_zero_block(filename, fd) == EXIT_FAILURE
			|| read_prog(filename, fd, player) == EXIT_FAILURE)
	{
		close_fd(fd);
		return (EXIT_FAILURE);
	}
	return (close_fd(fd));
}

void	print_player(t_player *p)
{
	ft_printf("Player num %d (%#0x)\n", p->num, ~p->num);
	ft_printf("header :\n");
	ft_printf("-> magic = %#0x\n", p->header.magic);
	ft_printf("-> name = %s\n", p->header.prog_name);
	ft_printf("-> size = %d\n", p->header.prog_size);
	ft_printf("-> comment = %s\n", p->header.comment);
}

t_exit	parsing(int argc, char **argv, t_vm *vm)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		vm->players_number += 1;
		if (parse_player(argv[i], &vm->player[i - 1], i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		print_player(&vm->player[i - 1]); //DEBUG
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

void	clean_all(void)
{
	int		i;

	i = 0;
	while (i < g_vm->players_number)
	{
		ft_strdel(&g_vm->player[i].prog);
		i++;
	}
}

int	main (int argc, char **argv)
{
	t_vm	vm;

	ft_bzero(&vm, sizeof(vm));
	g_vm = &vm;
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
