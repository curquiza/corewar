#include "asm.h"

static void			print_params(t_ast *ast)
{
	unsigned int i;
	unsigned int pad;

	i = 0;
	pad = 0;
	while (i < ast->opcode->param_nb)
	{
		if ((ast->arg_type[i] & T_DIR) == T_DIR)
		{
			ft_printf("%s", "%");
			pad++;
		}
		if ((ast->arg_type[i] & T_LAB) == T_LAB)
		{
			ft_printf("%s", ":");
			pad++;
		}
		if (pad == 2)
			ft_printf("%-14s", ast->arguments[i]);
		else if (pad == 1)
			ft_printf("%-15s", ast->arguments[i]);
		else
			ft_printf("%-16s", ast->arguments[i]);
		i++;
	}
}

static void			print_opcode_ocp(unsigned char opcode, unsigned char ocp)
{
	if (ocp)
	{
		ft_printf("%21s%-2d%8d%6s", "", (unsigned int)ocp, (unsigned int)opcode,
			"");
	}
	else
		ft_printf("%21s%-2d%14s", "", (unsigned int)opcode, "");
}

static void			print_ast_stdout(t_ast **ast, unsigned char *output)
{
	int i;

	i = 0;
	while (ast[i])
	{
		if (ast[i]->label)
			ft_printf("%-5d%8s %5s:\n", ast[i]->offset, ":", ast[i]->label);
		if (ast[i]->opcode)
		{
			ft_printf("%-5d (%-3d) :%8s%-16s", ast[i]->offset, ast[i]->size, "",
				ast[i]->opcode->name);
			print_params(ast[i]);
			ft_putendl("");
			print_opcode_ocp(ast[i]->ocp, ast[i]->opcode->opcode);
			print_raw_params(ast[i], output);
			print_opcode_ocp(ast[i]->ocp, ast[i]->opcode->opcode);
			print_relative_params(ast[i], output);
			ft_putendl("");
		}
		i++;
	}
}

t_ex_ret		write_output_stdout(t_src_file *file)
{
	ft_printf("Program size : %d bytes\n", ft_swap_int(file->header.prog_size));
	ft_printf("Name: \"%s\"\n", file->header.prog_name);
	ft_printf("Comment: \"%s\"\n\n", file->header.comment);
	print_ast_stdout(file->ast, file->output);
	return (SUCCESS);
}
