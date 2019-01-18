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

	
void			free_arguments(char *arguments[MAX_ARGS_NUMBER])
{
	int i;

	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		ft_strdel(&arguments[i]);
		i++;
	}
}

void			free_ast_array(t_ast ***ast)
{
	int		i;

	if (!*ast)
		return ;
	i = 0;
	while ((*ast)[i])
	{
		// ft_printf("free nb: %d\n", i); // debug
		ft_strdel(&((*ast)[i])->label);
		free_arguments((*ast)[i]->arguments);
		free((*ast)[i]);
		i++;
	}
	free(*ast);
	*ast = NULL;
}

void			print_one_ast(t_ast *ast)
{
	if (!(ast->label))
		ft_printf("label null\n");
	else
		ft_printf("label: %s\n", ast->label);
	if (!(ast->opcode))
		ft_printf("opcode null\n");
	else
		ft_printf("opcode: %s\t%x\n", ast->opcode->name, ast->opcode->opcode);
	if (!*(ast->arguments))
		ft_printf("arguments null\n");
	else
	{
		ft_printf("arguments:\n");
		ft_puttab(ast->arguments);		
	}
	ft_printf("arg_type param1: %d\n", ast->arg_type[0]);
	ft_printf("arg_type param2: %d\n", ast->arg_type[1]);
	ft_printf("arg_type param3: %d\n", ast->arg_type[2]);
	ft_printf("ocp: %b\n", ast->ocp);
	ft_printf("size: %d\n", ast->size);
	ft_printf("offset: %d\n", ast->offset);
}

void			print_ast_array(t_ast **ast)
{
	int		i;
	
	i = 0;
	while (ast[i])
	{
		ft_printf("===== ast nb: %d\n", i);
		print_one_ast(ast[i]);
		i++;
		ft_printf("=====\n");			
	}
}