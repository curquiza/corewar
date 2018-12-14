#include "asm.h"

static int     get_comment(t_src_file *file, char *line)
{
    char    *start;
    int     size;
    
    if (ft_strchr(line, '"') == NULL\
        || ft_strrchr(line, '"') != (line + ft_strlen(line) - 1)
        || count_char(line, '"') > 2)
        return (parse_error(file->nb_line, ERR_QUOTE));
    start = line + (ft_strchr(line, '"') - line) + 1;
    size = ft_strlen(start) > COMMENT_LENGTH + 1 ? -1 : ft_strlen(start) - 1;
    if (size == -1)
        return (parse_error(file->nb_line, BIG_COMMENT));
    ft_memcpy(file->header.comment, start, size);
    return (SUCCESS);
}

t_ex_ret        parse_comment(t_src_file *file)
{
    char    *line;
    int     ret;

    while ((ret = get_trim_line(file->fd, &line)) == 1)
	{
        file->nb_line++;
        if (*line == '#' || *line == '\0')
        {
	        ft_strdel(&line);
            continue ;
        }
        else if ((ft_strncmp(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING))) == 0)
        {
            ret = get_comment(file, line);
            ft_strdel(&line);
            return (ret);        
        }
        else
            break ;
	    ft_strdel(&line);
    }
    ft_strdel(&line);
    if (ret == -1)
        return (ft_ret_err(ERR_GNL));
    if (ret == 0 || *(file->header.comment) == '\0')
        return (parse_error(file->nb_line, NO_COMMENT));
    return (SUCCESS);
}