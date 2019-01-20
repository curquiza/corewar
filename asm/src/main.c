#include "asm.h"

int g_flags = 0;

static int		open_file(char *filename)
{
	struct stat		s;
	int 			fd;
	char			*extension;

	extension = ft_strrchr(filename, '.');
	if (!extension || (ft_strcmp(extension, INPUT_EXT)) != 0)
		return (put_error(USAGE));
	if ((stat(filename, &s)) < 0)
		return (ft_ret_err2(filename, NO_EXIST));
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (ft_ret_err2(filename, PERM_DENIED));
	return (fd);
}

static void		init_src_file(t_src_file *file, char *filename)
{
	g_file = file;
    ft_bzero(file, sizeof(t_src_file));
    file->filename = filename;
	file->header.magic = COREWAR_EXEC_MAGIC;
}

void		print_header(t_header *header)
{
	ft_printf("== HEADER ==\n");
	ft_printf("magic: %x\n", header->magic);
	ft_printf("prog name: %s\n", header->prog_name);
	ft_printf("prog size: %d\n", header->prog_size);
	ft_printf("prog desc: %s\n", header->comment);
	ft_printf("============\n");
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
		filename = *argv++;
		init_src_file(&file, filename);
		if ((ret = open_file(filename)) == FAILURE)
		{
			status = FAILURE;
			continue ;
		}
		else
			file.fd = ret;
		if ((ret = parse(&file)) != SUCCESS)
			status = FAILURE ;
		if (file.header.prog_size > CHAMP_MAX_SIZE && (ret = encode(&file)) != SUCCESS)
			status = FAILURE ;	
		// print_header(&file.header);
		free_ast_array(&file.ast);
		free_symbol_table(&file.symbol_table);
	}
	// while (1);
	return (status);
}
