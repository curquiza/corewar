#include "asm.h"

t_ex_ret		init_label(t_label **label, t_token_list *tokens)
{
	if (!(*label = (t_label*)malloc(sizeof(t_label))))
		return (ft_ret_err(ERR_MALLOC));
	(*label)->label = tokens;
	return (SUCCESS);
}

void			free_label(t_label **label)
{
	free_tokens(&(*label)->label);
	label = NULL;
}