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

void            del(void *content, size_t content_size)
{
    (void)content_size;
    (void)content;
}

t_ex_ret        list_to_array(t_list *input, char ***array, int len)
{
    t_list      *list_tmp;
    char        **array_tmp;

    if (!(*array = (char**)malloc(sizeof(char*) * (len + 1))))
        return (ft_ret_err(ERR_MALLOC));
    (*array)[len] = 0;

    list_tmp = input;
    array_tmp = *array;
    while (list_tmp)
    {
        *array_tmp++ = list_tmp->content;
        list_tmp = list_tmp->next;
    }
    return (SUCCESS);
}