#include "asm.h"

t_ex_ret             parse(t_src_file *file, int fd)
{
    int     ret;

    ret = parse_name(file, fd);
    ret = (ret == SUCCESS ? parse_comment(file, fd) : FAILURE);
    if (!(g_flags & FLAG_A))
    	ret = (ret == SUCCESS ? write_output_file(file) : FAILURE);
    else
    	ft_printf("write to terminal");
    close (fd);
    return (ret);
}