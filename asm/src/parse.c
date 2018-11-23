#include "asm.h"

static void     get_name(t_src_file *file, char *line)
{
    char    *start;
    int     size;
    
    ft_printf("line: %s\n", line);
    start = line + ft_strlen(NAME_CMD_STRING);
    size = ft_strlen(start) > PROG_NAME_LENGTH ? PROG_NAME_LENGTH : ft_strlen(start);
    ft_printf("name: %s\tsize: %d\n", start, size);
    ft_memcpy(file->header.prog_name, start, size);
}

/*
** LINE := COMMENT | NAME | DESC | INSTR
*/
static int     parse_line(t_src_file *file, char *line)
{
    char    *trimed_line;
    char    *tmp;

    trimed_line = ft_strtrim(line);
    if (!trimed_line || *trimed_line == '\0')
    {
        ft_putendl("empty line");
	    ft_strdel(&trimed_line);
        return (SUCCESS);
    }
    if ((ft_strncmp(trimed_line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING))) == 0)
    {
        ft_putendl("parse programme name");
        get_name(file, trimed_line);
	    ft_strdel(&trimed_line);
        return (SUCCESS);        
    }
    if ((ft_strncmp(trimed_line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING))) == 0)
    {
        ft_putendl("parse programme description");
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

int             parse(t_src_file *file, int fd)
{
    char    *line;
    int     ret;

    ret = SUCCESS;
    while ((ret = get_next_line(fd, &line)) == 1)
	{
        if ((ret = parse_line(file, line)) != SUCCESS)
            break ;
	    ft_strdel(&line);
    }
	line ? ft_strdel(&line): 0;

    if (ret == -1)
        return (READ_ERROR);

    close (fd);
    return (ret);
}