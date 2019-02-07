#include "asm.h"

static unsigned int  get_size(t_ast *ast, unsigned int i)
{
	if ((ast->arg_type[i] & T_REG) == T_REG)
		return(NUM_REG_SIZE);
	else if ((ast->arg_type[i] & T_IND) == T_IND)
		return(IND_SIZE);
	else if ((ast->arg_type[i] & T_DIR) == T_DIR)
		return(get_dir_size(ast->opcode->index));
	return (0);
}

static void		print_relative_params(t_ast *ast, unsigned char *output)
{
	unsigned int i;
	unsigned int size;
	unsigned int start;
	unsigned short *tmp;

	tmp = NULL;
	start = ast->offset + 1;
	if (ast->ocp)
		start++;
	i = 0;
	while (i < ast->opcode->param_nb)
	{
		size = get_size(ast, i);
		if (size == 1)
			ft_printf("%-16d", output[start]);
		else if (size == 2)
		{
			ft_printf("%-16d",
				(short)ft_swap_short(*(unsigned short*)(output + start)));
		}
		else if (size == 4)
		{
			ft_printf("%-16d",
				(int)ft_swap_int(*(unsigned int*)(output + start)));
		}
		start += size;
		i++;
	}
	ft_printf("\n");
}

static void		print_raw_params(t_ast *ast, unsigned char *output)
{
	unsigned int i;
	unsigned int j;
	unsigned int size;
	unsigned int start;

	start = ast->offset + 1;
	if (ast->ocp)
		start++;
	i = 0;
	while (i < ast->opcode->param_nb)
	{
		size = get_size(ast, i);
		j = 0;
		while (j < size)
		{
			ft_printf("%-4d", output[start++]);
			j++;
		}
		i++;
		if (size == 1)
			ft_printf("%-12s", "");
		if (size == 2)
			ft_printf("%-8s", "");
	}
	ft_printf("\n");
}

static void		print_params(t_ast *ast)
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
	ft_printf("\n");
}

void		print_ast_stdout(t_ast **ast, unsigned char *output)
{
	int i;

	i = 0;
	while (ast[i])
	{
		if (ast[i]->label)
			ft_printf("%-5d%8s %5s:\n", ast[i]->offset, ":", ast[i]->label);
		if (ast[i]->opcode)
		{
			ft_printf("%-5d (%-3d) :%8s%-16s", ast[i]->offset, ast[i]->size, "", ast[i]->opcode->name);

			print_params(ast[i]);
			if (ast[i]->ocp)
				ft_printf("%21s%-2d%8d%6s", "", ast[i]->opcode->opcode, ast[i]->ocp, "");
			else
				ft_printf("%21s%-2d%14s", "", ast[i]->opcode->opcode, "");
			print_raw_params(ast[i], output);
			if (ast[i]->ocp)
				ft_printf("%21s%-2d%8d%6s", "", ast[i]->opcode->opcode, ast[i]->ocp, "");				
			else
				ft_printf("%21s%-2d%14s", "", ast[i]->opcode->opcode, "");
			print_relative_params(ast[i], output);
			ft_printf("\n");
		}
		i++;
	}
}

t_ex_ret	write_output_stdout(t_src_file *file)
{
	ft_printf("Program size : %d bytes\n", ft_swap_int(file->header.prog_size));
	ft_printf("Name: \"%s\"\n", file->header.prog_name);
	ft_printf("Comment: \"%s\"\n\n", file->header.comment);
	print_ast_stdout(file->ast, file->output);
	return (SUCCESS);
}