#include "asm.h"

int			parse_direct(t_ast *ast, t_token_list *tokens, int pos)
{
	if (tokens->token->type != DIRECT || !tokens->next)
		return (-1);
	else
		tokens = tokens->next;
	if (tokens->token->type == STRING && ft_is_int(tokens->token->str) == TRUE)
	{
		ast->arg_type[pos] = T_DIR;
		ast->arguments[pos] = ft_strdup(tokens->token->str);
		ast->size += DIR_SIZE;
		tokens = tokens->next;
		return (2);
	}
	if (tokens->token->type != COLON || !tokens->next)
		return (-1);
	else
		tokens = tokens->next;
	if (tokens->token->type == STRING && is_label_string(tokens->token->str) == TRUE)
	{
		ast->arg_type[pos] = T_DIR | T_LAB;
		ast->arguments[pos] = ft_strdup(tokens->token->str);
		ast->size += DIR_SIZE;
		tokens = tokens->next;
		return (3);
	}
	return (-1);
}

int			parse_indirect(t_ast *ast, t_token_list *tokens, int pos)
{
	if (tokens->token->type == STRING && ft_is_int(tokens->token->str) == TRUE)
	{
		ast->arg_type[pos] = T_IND;
		ast->arguments[pos] = ft_strdup(tokens->token->str);
		ast->size += IND_SIZE;
		tokens = tokens->next;
		return (1);
	}
	if (tokens->token->type == STRING && is_label_string(tokens->token->str) == TRUE)
	{
		ast->arguments[pos] = ft_strdup(tokens->token->str);
		ast->size += IND_SIZE;
		tokens = tokens->next;
		return (1);
	}	
	return (-1);
}

int			parse_registre(t_ast *ast, t_token_list *tokens, int pos)
{
	if (tokens->token->type == STRING && is_registre(tokens->token->str) == TRUE)
	{
		ast->arg_type[pos] = T_REG;
		ast->arguments[pos] = ft_strdup(tokens->token->str);
		ast->size += REG_SIZE;
		tokens = tokens->next;
		return (1);
	}	
	return (-1);
}

t_token_list	*move_tokens(t_token_list *tokens, int move)
{
	while(move--)
		tokens = tokens->next;
	return (tokens);
}

t_ex_ret		apply_parse_param(t_arg_type param, t_ast *ast, t_token_list **tokens, int pos)
{
	int ret;

	if (((param & T_REG) == T_REG)\
		&& ((ret = parse_registre(ast, *tokens, pos)) != -1))
	{
		*tokens = move_tokens(*tokens, ret);
		return (SUCCESS);
	}
	if (((param & T_DIR) == T_DIR)\
		&& ((ret = parse_direct(ast, *tokens, pos)) != -1))
	{
		*tokens = move_tokens(*tokens, ret);
		return (SUCCESS);
	}
	if (((param & T_IND) == T_IND)\
		&& ((ret = parse_indirect(ast, *tokens, pos)) != -1))
	{
		*tokens = move_tokens(*tokens, ret);
		return (SUCCESS);
	}
	return (FAILURE);
}