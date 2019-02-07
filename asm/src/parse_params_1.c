#include "asm.h"

/*
** One parameter
*/

t_ex_ret		parse_parameters(t_ast *ast, t_token_list **tokens, int nb_line)
{
	unsigned int i;

	i = 0;			
	while (i < ast->opcode->param_nb)
	{
		if (apply_parse_param(ast->opcode->param_type[i], ast, tokens, i)
			== FAILURE)
			return (parse_error(nb_line, INVALID_PARAM));
		i++;
		if (!(*tokens = skip_whitespaces(*tokens)))
			break ;
		if ((*tokens)->token->type == SEPARATOR)
		{
			*tokens = (*tokens)->next;
			*tokens = skip_whitespaces(*tokens);
		}
		else
			break ;
	}
	if (i != ast->opcode->param_nb)
		return (parse_error(nb_line, INVALID_TOKEN));
	return (SUCCESS);
}
