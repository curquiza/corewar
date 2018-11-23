#include "asm.h"

int g_flags = 0;

static int		exit_error(char *e)
{
	ft_putendl_fd(e, STDERR_FILENO);
	return (FAILURE);
}

static void		put_error(enum e_error error, char *filename)
{
	ft_putstr_fd(PROG_NAME, STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	if (error == NO_EXIST)
		ft_putendl_fd(ERR_OPEN, STDERR_FILENO);
	if (error == PERM_DENIED)
		ft_putendl_fd(ERR_PERM, STDERR_FILENO);
	if (error == READ_ERROR)
		ft_putendl_fd(ERR_READ, STDERR_FILENO);		
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

static void		init_src_file(t_src_file *file)
{
	g_file = file;
    ft_bzero(file, sizeof(t_src_file));
	file->header.magic = COREWAR_EXEC_MAGIC;
}

static void		print_header(t_header *header)
{
	ft_printf("magic: %x\nprog name: %s\nprog size: %d\nprog desc: %s\n", header->magic, header->prog_name, header->prog_size, header->comment);
}

int				main (int argc, char **argv)
{
	int			ret;
	char		*filename;
	t_src_file	file;

	if (argc == 1)
		return (exit_error(USAGE));
	if ((get_options(&argc, &argv)) < 0)
		return (exit_error(ILLEGAL_OPTION));
	while (argc--)
	{
		init_src_file(&file);
		filename = *argv++;
		if ((ret = open_file(filename)) < 0)
			put_error(ret, filename);
		else
		{
			ft_printf("parsing file: %s\n", filename);
			if ((ret = parse(&file, ret)) != SUCCESS)
				put_error(ret, filename);
			print_header(&file.header);
		}
	}
	return (SUCCESS);
}
