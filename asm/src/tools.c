#include "asm.h"

int     get_trim_line(const int fd, char **line)
{
    char    *tmp;
    int     ret;

    tmp = NULL;
    ret = get_next_line(fd, line);
    if (*line && !(tmp = ft_strtrim(*line)))
        put_error_code(ERR_MALLOC, -1);
    *line ? free(*line) : 0;
    tmp ? *line = tmp : 0;
    return (ret);
}

int      count_char(char *s, char c)
{
    int     count;

    count = 0;
    while (*s)
        *s++ == c ? count++ : 0;
    return (count);
}