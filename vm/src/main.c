#include "vm.h"

int	close_fd(int fd)
{
	char	*fd_str;

	if (close(fd) == -1)
	{
		fd_str = ft_itoa(fd);
		perror(fd_str);
		ft_strdel(&fd_str);
		return (FAILURE);
	}
	return (SUCCESS);
}

int read_file(char *filename)
{
	int		fd;

	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		perror(filename);
		return (FAILURE);
	}
	ft_printf("ouvert :)\n"); // DEBUG
	return (close_fd(fd));
}

int parsing(int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (read_file(argv[i]) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int main (int argc, char **argv)
{
	if (argc <= 1)
	{
		ft_printf("Usage : ./corewar <champion>\n");
		exit(EXIT_FAILURE);
	}
	if (parsing(argc, argv) == FAILURE)
		exit(EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
