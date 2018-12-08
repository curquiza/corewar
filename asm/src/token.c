#include "asm.h"

t_ex_ret		link_token(t_src_file *file, char *line, int len)
{
	t_ex_ret	ret;
	t_token		*token;

	if ((ret = create_token(&token, line, len)) == SUCCESS)
	{
		add_token(&(file->tokens), token);
		file->current = token;
	}
	return (ret);
}

t_ex_ret		create_token(t_token **elem, char *line, int len)
{
	if (!(*elem = (t_token*)malloc(sizeof(t_token))))
		return (ft_ret_err(ERR_MALLOC));
	if (!((*elem)->str = ft_strsub(line, 0, len)))
		return (ft_ret_err(ERR_MALLOC));
	(*elem)->arg_type = 0;
	(*elem)->prev = NULL;
	(*elem)->next = NULL;
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

void			remove_current_token(t_src_file *file)
{
	t_token	*tmp;

	tmp = file->current;
	file->current = file->current->prev;
	tmp->prev->next = tmp->next;
	free (tmp->str);
	free (tmp);

}

void			print_tokens(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	ft_printf("-------\n");
	while (tmp)
	{
		ft_printf("%-20s\t%d\n",tmp->str, tmp->arg_type);
		tmp = tmp->next;
	}
	ft_printf("-------\n");
}

void			print_rev_tokens(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	ft_printf("-------\n");
	while (tmp)
	{
		ft_printf("%-20s\t%d\n",tmp->str, tmp->arg_type);
		tmp = tmp->prev;
	}
	ft_printf("-------\n");
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


