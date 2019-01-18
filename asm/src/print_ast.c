#include "asm.h"

void			print_one_ast(t_ast *ast)
{
	ft_printf("--- ast\n");
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
	ft_printf(RED"--- ast\n"DEF);
}

void			print_ast_array(t_ast **ast)
{
	int		i;
	
	i = 0;
	while (ast[i])
	{
		ft_printf("\n===== ast nb: %d\n", i);
		print_one_ast(ast[i]);
		i++;
		ft_printf("=====\n");			
	}
}