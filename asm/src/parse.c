#include "asm.h"

t_ex_ret             parse(t_src_file *file, int fd)
{
    int     ret;

    ret = parse_name(file, fd);
    ret == SUCCESS ? parse_comment(file, fd) : 0;
    close (fd);
    return (ret);
}