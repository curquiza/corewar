#include "asm.h"

int g_flags = 0;

static int		open_file(char *filename)
{
	struct stat		s;
	int 			fd;
	
	if ((stat(filename, &s)) < 0)
		return (ft_ret_err2(filename, NO_EXIST));
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (ft_ret_err2(filename, PERM_DENIED));
	return (fd);
}

static void		init_src_file(t_src_file *file)
{
	g_file = file;
    ft_bzero(file, sizeof(t_src_file));
	file->header.magic = COREWAR_EXEC_MAGIC;
	file->header.prog_size = sizeof(t_header);
}

void		print_header(t_header *header)
{
	ft_printf("== HEADER ==\n");
	ft_printf("magic: %x\n", header->magic);
	ft_printf("prog name: %s\n", header->prog_name);
	ft_printf("prog size: %d\n", header->prog_size);
	ft_printf("prog desc: %s\n", header->comment);
}

int				main (int argc, char **argv)
{
	int			ret;
	int			status;
	char		*filename;
	t_src_file	file;

	status = SUCCESS;
	if (argc == 1)
		return (put_error(USAGE));
	if ((get_options(&argc, &argv)) < 0)
		return (put_error(ILLEGAL_OPTION));
	while (argc--)
	{
		init_src_file(&file);
		filename = *argv++;
		// ft_printf("file: %s", filename);
		if ((ret = open_file(filename)) == FAILURE)
		{
			status = FAILURE;
			continue ;
		}
		if ((ret = parse(&file, ret)) != SUCCESS)
			status = FAILURE ;
		// print_header(&file.header);
	}
	return (status);
}
