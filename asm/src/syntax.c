#include "asm.h"

t_ex_ret	check_syntax(int line, t_token *current, t_token *new)
{
	(void)line;
	(void)current;
	(void)new;

	// if (new->arg_type == 0)
	// {
		// ft_printf("no pretypage");
		// get_token_type(new)
	// }
	// ft_printf("SYNTAX\ncurrent: %s\tnew: %s\n", current->str, new->str);
	// if (current == NULL && new->arg_type != T_LAB)
		// parse_error(line, "Label execpted!");
	return (FAILURE);
}