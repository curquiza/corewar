#include "asm.h"

t_ex_ret		parse(t_src_file *file, int fd)
{
	int		ret;

	ret = parse_name(file, fd);
	ret = (ret == SUCCESS ? parse_comment(file, fd) : FAILURE);
	ret = (ret == SUCCESS ? parse_instr(file, fd) : FAILURE);

	if (!(g_flags & FLAG_A))
		ret = (ret == SUCCESS ? write_output_file(file) : FAILURE);
	else
		write_output_stdout(file);
	close(fd);
	return (ret);
}