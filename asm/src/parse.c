#include "asm.h"

t_ex_ret		parse(t_src_file *file, int fd)
{
	if ((parse_name(file, fd)) == FAILURE)
		return (FAILURE);
	if ((parse_comment(file, fd)) == FAILURE)
		return (FAILURE);
	if ((parse_instr(file, fd)) == FAILURE)
		return (FAILURE);

	if (!(g_flags & FLAG_A))
	{
		if ((write_output_file(file)) == FAILURE)
			return (FAILURE);
	}
	else
		write_output_stdout(file);

	close(fd);
	return (SUCCESS);
}