#include "asm.h"

int g_flags = 0;

static int		exit_error(char *e)
{
	ft_putendl_fd(e, STDERR_FILENO);
	return (FAILURE);
}

static void		put_error(enum e_error error, char *filename)
{
	ft_putstr(PROG_NAME);
	ft_putstr(filename);
	if (error == NO_EXIST)
		ft_putendl_fd(ERR_OPEN, STDERR_FILENO);
	if (error == PERM_DENIED)
		ft_putendl_fd(ERR_PERM, STDERR_FILENO);
}

static int		open_file(char *filename)
{
	struct stat		s;
	int 			fd;
	
	if ((stat(filename, &s)) < 0)
		return (NO_EXIST);
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (PERM_DENIED);
	
	return (fd);
}

int				main (int argc, char **argv)
{
	int		ret;
	char	*file;

	if (argc == 1)
		return (exit_error(USAGE));
	if ((get_options(&argc, &argv)) < 0)
		return (exit_error(ILLEGAL_OPTION));
	while (argc--)
	{
		file = *argv++;
		if ((ret = open_file(file)) < 0)
			put_error(ret, file);
		else
			ft_printf("parsing file: %s\n", file);
	}
	return (SUCCESS);
}
