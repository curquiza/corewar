#include "vm.h"

exit_t	close_fd(int fd)
{
	char	*fd_str;

	if (close(fd) == -1)
	{
		fd_str = ft_itoa(fd);
		perror(fd_str);
		ft_strdel(&fd_str);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/*exit_t read_file*/

exit_t process_file(char *filename)
{
	int		fd;

	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		perror(filename);
		return (EXIT_FAILURE);
	}
	ft_printf("ouvert :)\n"); // DEBUG
	return (close_fd(fd));
}

exit_t parsing(int argc, char **argv)
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

int main (int argc, char **argv)
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
