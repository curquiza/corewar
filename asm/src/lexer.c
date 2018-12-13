#include "asm.h"

/*
** lexer take a line and return a list of tokens.
*/

t_ex_ret			lexer(t_token **tokens, char *line)
{
	
	link_token(tokens, line, ft_strlen(line));

	return (SUCCESS);
}
