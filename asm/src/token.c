#include "asm.h"

t_ex_ret		link_token(t_token **tokens, char *line, int len, t_type type)
{
	t_ex_ret	ret;
	t_token		*new;

	if ((ret = create_token(&new, line, len, type)) == SUCCESS)
	{
		add_token(tokens, new);
	}
	return (ret);
}

t_ex_ret		create_token(t_token **elem, char *line, int len, t_type type)
{
	if (!(*elem = (t_token*)malloc(sizeof(t_token))))
		return (ft_ret_err(ERR_MALLOC));
	if (!((*elem)->str = ft_strsub(line, 0, len)))
		return (ft_ret_err(ERR_MALLOC));
	(*elem)->prev = NULL;
	(*elem)->next = NULL;
	(*elem)->type = type;
	return (SUCCESS);
}

void			add_token(t_token **tokens, t_token *new)
{
	t_token	*tmp;

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

void			print_tokens(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	ft_printf("---\n");
	while (tmp)
	{
		ft_printf("%-30s",tmp->str);
		print_token_type(tmp->type);
		tmp = tmp->next;
	}
	ft_printf("---\n");
}

void			free_tokens(t_token **tokens)
{
	t_token	*tmp;
	t_token	*prev;

	if (!*tokens)
		return ;
	tmp = *tokens;
	while (tmp)
	{
		free (tmp->str);
		prev = tmp;
		tmp = tmp->next;
		free(prev);
	}
	*tokens = NULL;
}


