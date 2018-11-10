#include "vm.h"

void	fill_memory(char value)
{
	(void)value;
}

t_exit	read_and_fill(char *filename, char fd, int mem_offset)
{
	int		i;
	char	buff[1];
	int		read_ret;

	i = mem_offset;
	while (i < MEM_SIZE)
	{
		read_ret = read(fd, buff, 1);
		if (read_ret == -1)
			return (read_error(filename));
		if (read_ret == 0)
			break;
		else
			fill_memory(buff[0]);
	}
	return (EXIT_SUCCESS);
}

uint32_t str_to_uint32(char *str)
{
	uint32_t		rslt;

	rslt = 0;
	rslt = (rslt | (t_byte)str[0]) << 8;
	rslt = (rslt | (t_byte)str[1]) << 8;
	rslt = (rslt | (t_byte)str[2]) << 8;
	rslt |= (t_byte)str[3];
	return (rslt);
}

t_exit	read_magic(char *filename, int fd)
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
	printf("real magic = %0x\n", COREWAR_EXEC_MAGIC); //DEBUG
	printf("my magic = %0x\n", str_to_uint32(buff));   //DEBUG
	return (EXIT_SUCCESS);
}

t_exit	process_file(char *filename)
{
	int		fd;

	if ((fd = open_file(filename)) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	read_magic(filename, fd);
	/*read_and_fill(filename, fd, 0);*/
	return (close_fd(fd));
}

t_exit	parsing(int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (process_file(argv[i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
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
	if (init_check() == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	if (argc <= 1)
	{
		print_usage();
		exit(EXIT_FAILURE);
	}
	if (parsing(argc, argv) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
