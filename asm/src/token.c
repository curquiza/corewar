#include "asm.h"

static t_type 			get_token_type(char *token_name)
{
	t_type	type;

	type = NONE;
	if (is_whitespace(*token_name))
		type = WHITESPACE;
	if (is_special_char(*token_name))
		type = which_special_char(*token_name);
	if (is_string_char(*token_name))
	{
		type |= STRING;
		// if (ft_is_int(token_name))
		// 	type |= INTEGER;
		// if (is_registre(token_name))
		// 	type |= REGISTRE;
		// if (is_opcode(token_name))
		// 	type |= OPCODE;
		// if (is_label_string(token_name))
		// 	type |= LABEL;
	}
	return (type);
}

// static t_ex_ret		create_token(t_token **elem, char **token_name)
// {
// 	if (!(*elem = (t_token*)malloc(sizeof(t_token))))
// 		return (ft_ret_err(ERR_MALLOC));
// 	(*elem)->str = *token_name;
// 	(*elem)->prev = NULL;
// 	(*elem)->next = NULL;
// 	(*elem)->type = 0;
// 	(*elem)->line = 0;
// 	(*elem)->col = 0;
// 	return (SUCCESS);
// }

static t_ex_ret		create_token(t_token_list **elem, char **token_name)
{
	t_token *token;

	if (!(token = (t_token*)malloc(sizeof(t_token))))
		return (ft_ret_err(ERR_MALLOC));
	token->str = *token_name;
	token->type = 0;
	token->line = 0;
	token->col = 0;
	if (!(*elem = (t_token_list*)malloc(sizeof(t_token_list))))
		return (ft_ret_err(ERR_MALLOC));
	(*elem)->token = token;
	(*elem)->next = NULL;
	(*elem)->prev = NULL;
	return (SUCCESS);
}

// static void			add_token(t_token **tokens, t_token *new)
// {
// 	t_token	*tmp;

// 	if (!*tokens)
// 	{
// 		*tokens = new;
// 		return ;
// 	}
// 	tmp = *tokens;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	tmp->next = new;
// 	new->prev = tmp;
// 	return ;
// }

static void			add_token(t_token_list **tokens, t_token_list *new)
{
	t_token_list	*tmp;

	if (!*tokens)
	{
		*tokens = new;
		return ;
	}
	tmp = *tokens;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return ;
}

// t_ex_ret			link_token(t_token **tokens, char **token_name, int line, int col)
// {
// 	t_ex_ret	ret;
// 	t_token		*new;

// 	if ((ret = create_token(&new, token_name)) == SUCCESS)
// 	{
// 		new->line = line;
// 		new->col = col;
// 		new->type = get_token_type(*token_name);
// 		add_token(tokens, new);
// 	}
// 	return (ret);
// }

t_ex_ret			link_token(t_token_list **tokens, char **token_name, int line, int col)
{
	t_ex_ret			ret;
	t_token_list		*new;

	if ((ret = create_token(&new, token_name)) == SUCCESS)
	{
		new->token->line = line;
		new->token->col = col;
		new->token->type = get_token_type(*token_name);
		add_token(tokens, new);
	}
	return (ret);
}

static void				free_token(t_token *token)
{
	free(token->str);
	free(token);
}

void				free_tokens(t_token_list **tokens)
{
	t_token_list	*tmp;
	t_token_list	*prev;

	if (!*tokens)
		return ;
	tmp = *tokens;
	while (tmp)
	{
		free_token(tmp->token);
		prev = tmp;
		tmp = tmp->next;
		free(prev);
	}
	*tokens = NULL;
}


