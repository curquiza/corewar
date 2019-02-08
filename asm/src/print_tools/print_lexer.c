#include "asm.h"

static void		print_token_type(t_type type)
{
	if (type == NONE)
		ft_putstr("/!\\ NONE");
	if (type == WHITESPACE)
		ft_putstr("WHITESPACE");
	if (type == COLON)
		ft_putstr("COLON");
	if (type == SEPARATOR)
		ft_putstr("SEPARATOR");
	if (type == DIRECT)
		ft_putstr("DIRECT");
	if (type & STRING)
		ft_putstr("STRING ");
	ft_putendl("");
}

void			print_tokens(t_token_list *tokens)
{
	t_token_list	*tmp;

	tmp = tokens;
	ft_printf(RED"\n--- lex\n"DEF);
	while (tmp)
	{
		ft_printf("%d-%d %-30s", tmp->token->line, tmp->token->col,
			tmp->token->str);
		print_token_type(tmp->token->type);
		tmp = tmp->next;
	}
	ft_printf("--- lex\n");
}
