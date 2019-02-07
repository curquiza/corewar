#include "asm.h"

int					get_dir_size(int index)
{
	if (index)
		return (NUM_INDEX_SIZE);
	return (DIR_SIZE);
}

int					parse_direct_label(t_ast *ast, t_token_list *tokens, int pos)
{
	if (tokens->token->type != COLON || !tokens->next)
		return (-1);
	else
		tokens = tokens->next;
	if (tokens->token->type == STRING && is_label_string(tokens->token->str) == TRUE)
	{
		ast->arg_type[pos] = T_DIR | T_LAB;
		ast->arguments[pos] = ft_strdup(tokens->token->str);
		ast->size += get_dir_size(ast->opcode->index);
		tokens = tokens->next;
		return (3);
	}
	return (-1);
}

int					parse_direct(t_ast *ast, t_token_list *tokens, int pos)
{
	if (tokens->token->type != DIRECT || !tokens->next)
		return (-1);
	else
		tokens = tokens->next;
	if (tokens->token->type == STRING && ft_is_int(tokens->token->str) == TRUE)
	{
		ast->arg_type[pos] = T_DIR;
		ast->arguments[pos] = ft_strdup(tokens->token->str);
		ast->size += get_dir_size(ast->opcode->index);
		tokens = tokens->next;
		return (2);
	}
	return (parse_direct_label(ast, tokens, pos));
}

int					parse_indirect(t_ast *ast, t_token_list *tokens, int pos)
{
	if (tokens->token->type == STRING && ft_is_int(tokens->token->str) == TRUE) // is short !!!
	{
		ast->arg_type[pos] = T_IND;
		ast->arguments[pos] = ft_strdup(tokens->token->str);
		ast->size += IND_SIZE;
		tokens = tokens->next;
		return (1);
	}
	if (tokens->token->type != COLON || !tokens->next)
		return (-1);
	else
		tokens = tokens->next;	
	if (tokens->token->type == STRING && is_label_string(tokens->token->str) == TRUE)
	{
		ast->arg_type[pos] = T_IND | T_LAB;
		ast->arguments[pos] = ft_strdup(tokens->token->str);
		ast->size += IND_SIZE;
		tokens = tokens->next;
		return (2);
	}	
	return (-1);
}

int					parse_registre(t_ast *ast, t_token_list *tokens, int pos)
{
	if (tokens->token->type == STRING && is_registre(tokens->token->str) == TRUE)
	{
		ast->arg_type[pos] = T_REG;
		ast->arguments[pos] = ft_strdup(tokens->token->str);
		ast->size += NUM_REG_SIZE;
		tokens = tokens->next;
		return (1);
	}	
	return (-1);
}
