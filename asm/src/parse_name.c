#include "asm.h"

static int     get_name(t_src_file *file, char *line)
{
    char    *start;
    int     size;
    
    if (ft_strchr(line, '"') == NULL\
        || ft_strrchr(line, '"') != (line + ft_strlen(line) - 1)
        || count_char(line, '"') > 2)
        return (parse_error(0, ERR_QUOTE));

    start = line + (ft_strchr(line, '"') - line) + 1;
    size = ft_strlen(start) > PROG_NAME_LENGTH ? PROG_NAME_LENGTH : ft_strlen(start) - 1;
    ft_memcpy(file->header.prog_name, start, size);

    return (SUCCESS);
}

t_ex_ret        parse_name(t_src_file *file, int fd)
{
    char    *line;
    int     ret;

    while ((ret = get_trim_line(fd, &line)) == 1)
	{
        ft_printf("line: %s\n", line);
        if (*line == '#' || *line == '\0')
        {
	        ft_strdel(&line);
            continue ;
        }
        else if ((ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING))) == 0)
        {
            get_name(file, line);
            ft_strdel(&line);
            return (SUCCESS);        
        }
        else
            break ;
	    ft_strdel(&line);
    }
    if (ret == -1)
        return (ft_ret_err(ERR_READ));
    if (ret == 0 || *(file->header.prog_name) == '\0')
        return (ft_ret_err(NO_NAME));
    return (SUCCESS);
}