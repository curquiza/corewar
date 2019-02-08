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

t_ex_ret	parse_error(int line, char *message)
{
	ft_dprintf(STDERR_FILENO, "Error line %d: %s\n", line, message);
	return (FAILURE);
}

t_ex_ret	parse_error_token(int line, char *token, char *message)
{
	ft_dprintf(STDERR_FILENO, "Error line %d: <%s> %s\n", line, token, message);
	return (FAILURE);
}

t_ex_ret	label_not_found(char *label)
{
	ft_dprintf(STDERR_FILENO, "Error: <%s> %s\n", label, NO_LABEL);
	return (FAILURE);
}
