#include "asm.h"

t_ex_ret		init_ast_array(t_ast ***ast, int nb_line)
{
	int		i;

	if (!(*ast = (t_ast**)ft_memalloc(sizeof(t_ast*) * (nb_line + 1))))
		return (ft_ret_err(ERR_MALLOC));
	// (*ast)[nb_line] = 0; // retenir la taille
	i = 0;
	while (i < nb_line)
	{
		if (!((*ast)[i] = (t_ast*)ft_memalloc(sizeof(t_ast))))
			return (ft_ret_err(ERR_MALLOC));
		i++;
	}
	return (SUCCESS);
}

void			free_ast_array(t_ast ***ast)
{
	int		i;

	if (!*ast)
		return ;
	i = 0;
	while ((*ast)[i])
	{
		ft_printf("free nb: %d\n", i); // debug
		free_tokens(&((*ast)[i])->label);
		free_tokens(&((*ast)[i])->arguments);
		free((*ast)[i]);
		i++;
	}
	free(*ast);
	*ast = NULL;
}

void			print_ast_array(t_ast **ast)
{
	int		i;
	
	i = 0;
	while (ast[i])
	{
		ft_printf("===== ast nb: %d\n", i);		
		if (!(ast[i]->label))
			ft_printf("label null\n");
		else
			print_tokens(ast[i]->label);
		if (!(ast[i]->opcode))
			ft_printf("opcode null\n");
		else
			ft_printf("opcode: \n", ast[i]->opcode[0]);
		if (!(ast[i]->arguments))
			ft_printf("arguments null\n");
		else
			print_tokens(ast[i]->arguments);		
		if (!(ast[i]->size))
			ft_printf("size: %d\n", ast[i]->size);
		if (!(ast[i]->offset))
			ft_printf("offset: %d\n", ast[i]->offset);
		i++;
		ft_printf("=====\n");			
	}
}