#include "asm.h"

/*
** One parameter
*/

t_ex_ret		parse_parameters(t_ast *ast, t_token_list **tokens, int nb_line)
{
	unsigned int i;

	i = 0;
	// ft_printf("ast->opcode->param_nb: %d\n", ast->opcode->param_nb); // debug
	while (i < ast->opcode->param_nb)
	{
		if (apply_parse_param(ast->opcode->param_type[i], ast, tokens, i) == FAILURE)
			return (parse_error(nb_line, INVALID_PARAM));
			i++;

		if (!(*tokens = skip_whitespaces(*tokens)))
			break ;
		// ft_printf("str: %s\n", (*tokens)->token->str); // debug
		
		if ((*tokens)->token->type == SEPARATOR)
		{
			*tokens = (*tokens)->next;
			*tokens = skip_whitespaces(*tokens);
		}
		else
			break ;
		
	}
	// ft_printf("i: %d\n", i); // debug
	if (i != ast->opcode->param_nb)
		return (parse_error(nb_line, INVALID_TOKEN));
	return (SUCCESS);
}










































t_ex_ret		parse_live(t_ast *ast, t_token_list **tokens, int nb_line)
{
	unsigned int i;

	i = 0;
	while (i < ast->opcode->param_nb)
	{
		if (apply_parse_param(ast->opcode->param_type[i], ast, tokens, i) == FAILURE)
			return (parse_error(nb_line, INVALID_PARAM));
			i++;

		if (!(*tokens = skip_whitespaces(*tokens)))
			break ;
		
		if (*tokens && (*tokens)->token->type == SEPARATOR)
		{
			*tokens = (*tokens)->next;
			*tokens = skip_whitespaces(*tokens);
		}
		else
			break ;
		
	}
	if (i != ast->opcode->param_nb - 1)
		return (parse_error(nb_line, INVALID_TOKEN));
	return (SUCCESS);
}

t_ex_ret		parse_zjump(t_ast *ast, t_token_list **tokens, int nb_line)
{
	(void)ast;
	(void)tokens;
	(void)nb_line;
	
	return (SUCCESS);
}

t_ex_ret		parse_fork(t_ast *ast, t_token_list **tokens, int nb_line)
{
	(void)ast;
	(void)tokens;
	(void)nb_line;
	
	return (SUCCESS);
}

t_ex_ret		parse_lfork(t_ast *ast, t_token_list **tokens, int nb_line)
{
	(void)ast;
	(void)tokens;
	(void)nb_line;
	
	return (SUCCESS);
}

t_ex_ret		parse_aff(t_ast *ast, t_token_list **tokens, int nb_line)
{
	(void)ast;
	(void)tokens;
	(void)nb_line;
	
	return (SUCCESS);
}

/*
** One parameter
*/

t_ex_ret		parse_ld(t_ast *ast, t_token_list **tokens, int nb_line)
{
	unsigned int i;

	i = 0;
	while (i < ast->opcode->param_nb)
	{
		if (apply_parse_param(ast->opcode->param_type[i], ast, tokens, i) == FAILURE)
			return (parse_error_token(nb_line, (*tokens)->token->str, INVALID_PARAM));
			i++;

		if (!(*tokens = skip_whitespaces(*tokens)))
			break ;
		
		if (*tokens && (*tokens)->token->type == SEPARATOR)
		{
			*tokens = (*tokens)->next;
			*tokens = skip_whitespaces(*tokens);
		}
		else
			break ;
		
	}
	if (i != ast->opcode->param_nb - 1)
		return (parse_error_token(nb_line, (*tokens)->token->str, INVALID_TOKEN));
	return (SUCCESS);
}

/*
** OTHERS
*/



t_ex_ret		parse_st(t_ast *ast, t_token_list **tokens, int nb_line)
{
	(void)ast;
	(void)tokens;
	(void)nb_line;
	
	return (SUCCESS);
}

t_ex_ret		parse_add(t_ast *ast, t_token_list **tokens, int nb_line)
{
	(void)ast;
	(void)tokens;
	(void)nb_line;
	
	return (SUCCESS);
}

t_ex_ret		parse_sub(t_ast *ast, t_token_list **tokens, int nb_line)
{
	(void)ast;
	(void)tokens;
	(void)nb_line;
	
	return (SUCCESS);
}

t_ex_ret		parse_and(t_ast *ast, t_token_list **tokens, int nb_line)
{
	(void)ast;
	(void)tokens;
	(void)nb_line;
	
	return (SUCCESS);
}

t_ex_ret		parse_or(t_ast *ast, t_token_list **tokens, int nb_line)
{
	(void)ast;
	(void)tokens;
	(void)nb_line;
	
	return (SUCCESS);
}

t_ex_ret		parse_xor(t_ast *ast, t_token_list **tokens, int nb_line)
{
	(void)ast;
	(void)tokens;
	(void)nb_line;
	
	return (SUCCESS);
}



t_ex_ret		parse_ldi(t_ast *ast, t_token_list **tokens, int nb_line)
{
	(void)ast;
	(void)tokens;
	(void)nb_line;
	
	return (SUCCESS);
}

t_ex_ret		parse_sti(t_ast *ast, t_token_list **tokens, int nb_line)
{
	(void)ast;
	(void)tokens;
	(void)nb_line;
	
	return (SUCCESS);
}



t_ex_ret		parse_lld(t_ast *ast, t_token_list **tokens, int nb_line)
{
	(void)ast;
	(void)tokens;
	(void)nb_line;
	
	return (SUCCESS);
}

t_ex_ret		parse_lldi(t_ast *ast, t_token_list **tokens, int nb_line)
{
	(void)ast;
	(void)tokens;
	(void)nb_line;
	
	return (SUCCESS);
}
