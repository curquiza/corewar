#include "asm.h"

t_ex_ret		create_token(t_token **elem, char *line, int len, t_arg_type type)
{
	if (!(*elem = (t_token*)malloc(sizeof(t_token))))
		return (ft_ret_err(ERR_MALLOC));
	ft_bzero(*elem, sizeof(elem));
	if (!((*elem)->str = ft_strsub(line, 0, len)))
		return (ft_ret_err(ERR_MALLOC));
	(*elem)->arg_type = type;
	return (SUCCESS);
}

void			add_token(t_token **tokens, t_token *new)
{
	t_token	*tmp;

		ft_printf("plop");
	if (!*tokens)
	{
		ft_printf("first token");
		*tokens = new;
		return ;
	}
	tmp = *tokens;
	while (tmp->next)
		tmp = tmp->next;
	ft_printf("add token");
	tmp->next = new;
	new->prev = tmp;
	return ;
}

void			print_tokens(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		ft_printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
}
