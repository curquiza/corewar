#include "asm.h"

int g_flags = 0;

static int			open_file(char *filename)
{
	struct stat		s;
	int				fd;
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

static void			init_src_file(t_src_file *file, char *filename)
{
	ft_bzero(file, sizeof(t_src_file));
	file->filename = filename;
	file->header.magic = ft_swap_int(COREWAR_EXEC_MAGIC);
}

static void			cleaning(t_src_file *file)
{
	free_ast_array(&file->ast);
	free_symbol_table(&file->symbol_table);
	ft_tabdel(&file->input);
	free_tokens(&file->tokens);
}

static t_ex_ret		check_constants(void)
{
	if (MAX_ARGS_NUMBER == 4
		&& (MEM_SIZE == 4 * 1024)
		&& (CHAMP_MAX_SIZE == MEM_SIZE / 6)
		&& (NUM_REG_SIZE == 1)
		&& (IND_SIZE == 2)
		&& (DIR_SIZE == 4)
		&& (PROG_NAME_LENGTH == 128)
		&& (COMMENT_LENGTH == 2048))
	{
		return (SUCCESS);
	}
	return (ft_ret_err(BAD_CONFIG));
}

// grouper ret et status ??

int					main(int argc, char **argv)
{
	int			ret;
	int			status;
	char		*filename;
	t_src_file	file;

	check_constants();
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
		if ((ret = compile(&file)) != SUCCESS)
			status = FAILURE;
		cleaning(&file);
	}
	// while (1);
	return (status);
}
