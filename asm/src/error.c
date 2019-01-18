#include "asm.h"

t_ex_ret	put_error(char *e)
{
	ft_putendl_fd(e, STDERR_FILENO);
	return (FAILURE);
}

int			put_error_code(char *e, int code)
{
	ft_putendl_fd(e, STDERR_FILENO);
	return (code);
}

t_ex_ret     parse_error(int line, char *message)
{
    ft_dprintf(2, "Error line %d: %s\n", line, message);
    return (FAILURE);
}

t_ex_ret     parse_error_token(int line, char *token, char *message)
{
    ft_dprintf(2, "Error line %d: <%s> %s\n", line, token, message);
    return (FAILURE);
}