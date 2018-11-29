#include "asm.h"

int     get_trim_line(const int fd, char **line)
{
    char    *tmp;
    int     ret;

    ret = get_next_line(fd, line);
    if (!(tmp = ft_strtrim(*line)))
        put_error_code(ERR_MALLOC, -1);
    free(*line);
    *line = tmp;
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