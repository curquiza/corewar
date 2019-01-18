#include "asm.h"

/*
** parse_line: rules to define a valid isntruction.
*/

t_token_list	*skip_whitespaces(t_token_list *tokens)
{
	t_token_list	*current;

	if (!tokens)
		return (NULL);
	current = tokens;
	while (current)
	{
		if (current->token->type == WHITESPACE)
			current = current->next;
		else
			break ;
	}
	return (current);
}

t_ex_ret		parse_label(t_ast *ast, t_token_list **tokens, int nb_line)
{
	// parse label
	if (!(*tokens = skip_whitespaces(*tokens)))
		return (SUCCESS);
	// ft_printf("pl - token: %s\n", (*tokens)->token->str); // debug

	if ((*tokens)->token->type != STRING)
		return (parse_error_token(nb_line, (*tokens)->token->str, INVALID_TOKEN));
	else if (((*tokens)->token->type == STRING)
		&& (*tokens)->next
		&& ((*tokens)->next->token->type == COLON)) // euh, check label valid ?? is_label_string
	{
		ast->label = ft_strdup((*tokens)->token->str);
		*tokens = (*tokens)->next->next ? (*tokens)->next->next : NULL;		
		// return (SUCCESS);
	}
	return (SUCCESS);
}

t_ex_ret		parse_opcode(t_ast *ast, t_token_list **tokens, int nb_line)
{
	int		nb;

	if (!(*tokens = skip_whitespaces(*tokens)))
		return (SUCCESS);
	// ft_printf("po - token: %s\n", (*tokens)->token->str); // debug
	if ((*tokens)->token->type != STRING)
		return (parse_error_token(nb_line, (*tokens)->token->str,INVALID_TOKEN));
	else if ((nb = is_opcode((*tokens)->token->str)) != -1)
	{
		ast->opcode = &g_op_tab[nb];
		ast->size += 1;
		*tokens = (*tokens)->next ? (*tokens)->next : NULL;
		return (SUCCESS);
	}
	return (parse_error_token(nb_line, (*tokens)->token->str, INVALID_OPCODE));
}



t_ex_ret		parse_arguments(t_ast *ast, t_token_list **tokens, int nb_line)
{
	*tokens = skip_whitespaces(*tokens);
	if (!*tokens && ast->opcode)
		return (parse_error_token(nb_line, ast->opcode->name, NB_PARAMS));
	else if (!*tokens)
		return (SUCCESS);
	// ft_printf("pa - token: %s\n", (*tokens)->token->str); // debug
	if (parse_parameters(ast, tokens, nb_line) == FAILURE)
		return (FAILURE);

	return (SUCCESS);
}

t_ex_ret		parse_line(t_ast *ast, t_token_list *tokens, int nb_line)
{
	t_token_list *current_token;
	
	if (!tokens)
		return (SUCCESS);
	current_token = tokens;
	if ((parse_label(ast, &current_token, nb_line)) == FAILURE)
		return (FAILURE);
	if ((parse_opcode(ast, &current_token, nb_line)) == FAILURE)
		return (FAILURE);
	if ((parse_arguments(ast, &current_token, nb_line)) == FAILURE)
		return (FAILURE);
	// print_tokens(current_token); // debug

	return (SUCCESS);
}