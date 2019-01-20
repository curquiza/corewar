#include "asm.h"

void		print_params(t_ast *ast)
{
	unsigned int i;

	i = 0;
	while (i < ast->opcode->param_nb)
	{
		if ((ast->arg_type[i] & T_DIR) == T_DIR)
			ft_printf("%s", "%");
		if ((ast->arg_type[i] & T_LAB) == T_LAB)
			ft_printf("%s", ":");
		ft_printf("%s\t", ast->arguments[i]);
		i++;
	}
	ft_printf("\n");
}

void		print_ast_stdout(t_ast **ast)
{
	int i;

	i = 0;
	while (ast[i])
	{
		if (ast[i]->label)
			ft_printf("%-5d       :\t%s:\n", ast[i]->offset, ast[i]->label);
		if (ast[i]->opcode)
		{
			ft_printf("%-5d (%-3d) :\t\t%s\t", ast[i]->offset, ast[i]->size, ast[i]->opcode->name);

			print_params(ast[i]);
			if (ast[i]->ocp)
				ft_printf("            \t%d %d\n", ast[i]->opcode->param_nb, ast[i]->ocp);
			else
				ft_printf("            \t%d\t\n", ast[i]->opcode->param_nb);
			// print raw bytes
			ft_printf("            \t%d\n", ast[i]->opcode->param_nb);
			// print int bytes for addresse
		}
		ft_printf("\n");
		i++;
	}
}

t_ex_ret	write_output_stdout(t_src_file *file)
{
	ft_printf("Program size : %d bytes\n", file->header.prog_size);
	ft_printf("Name: \"%s\"\n", file->header.prog_name);
	ft_printf("Comment: \"%s\"\n\n", file->header.comment);
	print_ast_stdout(file->ast);
	return (SUCCESS);
}