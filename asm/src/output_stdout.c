#include "asm.h"

t_ex_ret	write_output_stdout(t_src_file *file)
{
	ft_printf("Program size: %d\n", file->header.prog_size);
	ft_printf("Name: \"%s\"\n", file->header.prog_name);
	ft_printf("Comment: \"%s\"\n", file->header.comment);
	
	return (SUCCESS);
}