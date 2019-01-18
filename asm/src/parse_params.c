#include "asm.h"

// DIRECT % VALUE | % : STRING

t_ex_ret		parse_direct(t_ast *ast, t_token_list **tokens, int pos)
{
	if ((*tokens)->token->type != DIRECT || !(*tokens)->next)
		return (FAILURE);
	else
		(*tokens) = (*tokens)->next;
	if ((*tokens)->token->type == STRING && ft_is_int((*tokens)->token->str) == TRUE)
	{
		ast->arguments[pos] = ft_strdup((*tokens)->token->str);
		ast->size += DIR_SIZE;
		(*tokens) = (*tokens)->next;
		return (SUCCESS);
	}
	if ((*tokens)->token->type != COLON || !(*tokens)->next)
		return (FAILURE);
	else
		(*tokens) = (*tokens)->next;
	if ((*tokens)->token->type == STRING && is_label_string((*tokens)->token->str) == TRUE)
	{
		ast->arguments[pos] = ft_strdup((*tokens)->token->str);
		ast->size += DIR_SIZE;
		(*tokens) = (*tokens)->next;
		return (SUCCESS);
	}
	return (FAILURE);
}

// INDIRECT VALUE | STRING

t_ex_ret		parse_indirect(t_ast *ast, t_token_list **tokens, int pos)
{
	if ((*tokens)->token->type == STRING && ft_is_int((*tokens)->token->str) == TRUE)
	{
		ast->arguments[pos] = ft_strdup((*tokens)->token->str);
		ast->size += IND_SIZE;
		(*tokens) = (*tokens)->next;
		return (SUCCESS);
	}
	if ((*tokens)->token->type == STRING && is_label_string((*tokens)->token->str) == TRUE)
	{
		ast->arguments[pos] = ft_strdup((*tokens)->token->str);
		ast->size += IND_SIZE;
		(*tokens) = (*tokens)->next;
		return (SUCCESS);
	}	
	return (FAILURE);
}

// REGISTRE r VALUE


t_ex_ret		parse_registre(t_ast *ast, t_token_list **tokens, int pos)
{
	if ((*tokens)->token->type == STRING && is_registre((*tokens)->token->str) == TRUE)
	{
		ast->arguments[pos] = ft_strdup((*tokens)->token->str);
		ast->size += REG_SIZE;
		(*tokens) = (*tokens)->next;
		return (SUCCESS);
	}	
	return (FAILURE);
}

t_ex_ret		apply_parse_param(t_arg_type param, t_ast *ast, t_token_list **tokens, int pos)
{
	t_token_list *current;

	current = *tokens;
		ft_printf("param: %d\n", param); // debug
	if ((param & T_DIR) == T_DIR)
	{
		ast->arg_type[pos] = T_DIR;
		ft_printf("apply_parse_param DIR\n"); // debug
		if (parse_direct(ast, &current, pos) == SUCCESS)
		{
			tokens = &current;
			return (SUCCESS);
		}
	}
	current = *tokens;

	if ((param & T_IND) == T_IND)
	{
		ast->arg_type[pos] = T_IND;
		ft_printf("apply_parse_param IND\n"); // debug
		if (parse_indirect(ast, &current, pos) == SUCCESS)
		{
			tokens = &current;
			return (SUCCESS);
		}
	}
	current = *tokens;

	if ((param & T_REG) == T_REG)
	{
		ast->arg_type[pos] = T_REG;
		ft_printf("apply_parse_param REG\n"); // debug
		if (parse_registre(ast, &current, pos) == SUCCESS)
		{
			tokens = &current;
			return (SUCCESS);
		}
	}
	return (FAILURE);
}