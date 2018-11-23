#include "asm.h"

/*
** LINE := COMMENT | NAME | DESC | INSTR
*/
int     parse_line(t_src_file *file, char *line)
{
    char    *trimed_line;
    char    *tmp;

    (void)file;

    trimed_line = ft_strtrim(line);
    if (!trimed_line || *trimed_line == '\0')
    {
        ft_putendl("empty line");
	    ft_strdel(&trimed_line);
        return (SUCCESS);
    }
    tmp = trimed_line;
    while (*tmp)
    {
        ft_putchar(*tmp++);
    }
    ft_putchar('\n');
	ft_strdel(&trimed_line);
    return (SUCCESS);
}

t_ex_ret             parse(t_src_file *file, int fd)
{
    int     ret;

    ret = parse_name(file, fd);
    ret == SUCCESS ? parse_comment(file, fd) : 0;
    close (fd);
    return (ret);
}