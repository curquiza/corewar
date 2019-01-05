#include "asm.h"

t_ex_ret		init_ast_array(t_ast ***ast, int nb_line)
{
	if (!(*ast = (t_ast**)malloc(sizeof(t_ast) * (nb_line + 1))))
		return (ft_ret_err(ERR_MALLOC));
	// ft_bzero(*ast, sizeof(t_ast) * (nb_line + 1));
	(*ast)[nb_line] = 0;
	return (SUCCESS);
}

static int 		len_ast_array(t_ast **ast)
{
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (ast[i])
		len++;
	return (len);
}

void			free_ast_array(t_ast ***ast)
{
	int		i;
	int		len;

	len = len_ast_array(*ast);
	i = 0;
	while (i < len)
	{
		free_label(&((*ast)[i])->label);
		// free_tokens(&((*ast)[i])->instr->arguments);
		i++;
	}
	free(*ast);
	ast = NULL;
}

void			print_ast_array(t_ast **ast)
{
	int		i;
	int		len;
	
	len = len_ast_array(ast);
	i = 0;
	while (i < len)
		ft_printf("%d\t", i++);
}