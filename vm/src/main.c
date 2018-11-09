#include "vm.h"

t_exit	close_fd(int fd)
{
	char	*fd_str;
	char	*err_str;

	if (close(fd) == -1)
	{
		fd_str = ft_itoa(fd);
		err_str = ft_strjoin("Close error: ", fd_str);
		perror(err_str);
		ft_strdel(&fd_str);
		ft_strdel(&err_str);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_exit	open_file(char *filename)
{
	int		fd;
	char	*err_str;

	if ((fd = open(filename, O_RDONLY)) <= 0)
	{
		err_str = ft_strjoin("Open error: ", filename);
		perror(err_str);
		ft_strdel(&err_str);
		return (EXIT_FAILURE);
	}
	return (fd);
}

t_exit	read_error(char *filename)
{
	char	*err_str;

	err_str = ft_strjoin("Read error: ", filename);
	perror(err_str);
	ft_strdel(&err_str);
	return (EXIT_FAILURE);
}

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

int32_t str_to_int32(char *str)
{
	int32_t		rslt;

	rslt = 0;
	rslt = (rslt | (byte_t)str[0]) << 8;
	rslt = (rslt | (byte_t)str[1]) << 8;
	rslt = (rslt | (byte_t)str[2]) << 8;
	rslt |= (byte_t)str[3];
	return (rslt);
}

t_exit	read_magic(char *filename, int fd)
{
	char	buff[5];
	int		read_ret;

	read_ret = read(fd, buff, 4);
	if (read_ret == -1)
		return (read_error(filename));
	buff[read_ret] = '\0';
	printf("real magic = %0x\n", COREWAR_EXEC_MAGIC);
	printf("my magic = %0x\n", str_to_int32(buff));
	return (EXIT_SUCCESS);
}

t_exit	process_file(char *filename)
{
	int		fd;

	if ((fd = open_file(filename)) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_printf("ouvert :)\n"); // DEBUG
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

int	main (int argc, char **argv)
{
	if (argc <= 1)
	{
		ft_printf("Usage : ./corewar <champion>\n");
		exit(EXIT_FAILURE);
	}
	if (parsing(argc, argv) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
