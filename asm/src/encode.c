#include "asm.h"

void			fill_ocp(t_ast *ast, int pos)
{
	if ((ast->arg_type[pos] & T_DIR)== T_DIR)
	{
		// ft_printf("ajout T_DIR %b\n", DIR_CODE << ((3 - pos) * 2)); // debug
		ast->ocp |= (DIR_CODE << ((3 - pos) * 2));
	}
	else if ((ast->arg_type[pos] & T_IND) == T_IND)
	{
		// ft_printf("ajout T_IND %b\n", IND_CODE << ((3 - pos) * 2)); // debug
		ast->ocp |= (IND_CODE << ((3 - pos) * 2));
	}
	else if ((ast->arg_type[pos] & T_REG) == T_REG)
	{
		// ft_printf("ajout T_REG %b\n", REG_CODE << ((3 - pos) * 2)); // debug
		ast->ocp |= (REG_CODE << ((3 - pos) * 2));
	}
}

unsigned char	create_ocp(t_ast *ast)
{
	unsigned int		i;
	
	if (!ast->opcode->ocp)
		return (0);
	i = 0;
	while (i < ast->opcode->param_nb)
	{
		fill_ocp(ast, i);
		// ft_printf("%d %b\n", i, ast->ocp); // debug
		i++;
	}
	return (ast->ocp);
}

unsigned short	get_indirect(t_src_file *file, int i, int j)
{
	if ((file->ast[i]->arg_type[j] & T_LAB) == T_LAB)
	{
		ft_printf("get_indirect label: %d\n", 0);
		return (0);
	}
	else
	{
		ft_printf("get_indirect value: %d\n", (unsigned short)ft_atoi(file->ast[i]->arguments[j]));
		return ((unsigned short)ft_atoi(file->ast[i]->arguments[j]));
	}
}

unsigned char	get_registre(char *r)
{
	ft_printf("get_registre: %d\n", ft_atoi(r + 1));
	return (ft_atoi(r + 1));
}

void			encode_parameters(t_src_file *file, int i, int pos)
{
	unsigned int		j;

	j = 0;
	while (j < file->ast[i]->opcode->param_nb)
	{
		if ((file->ast[i]->arg_type[j] & T_REG) == T_REG)
		{
			file->output[pos] = get_registre(file->ast[i]->arguments[j]);
			pos += NUM_REG_SIZE;
		}
		if ((file->ast[i]->arg_type[j] & T_IND) == T_IND)
		{
			file->output[pos] = get_indirect(file, i, j); // cast et ne recupere qu'une seule valeur...
			pos += IND_SIZE;
		}		
		j++;
	}

}

t_ex_ret		encode_instructions(t_src_file *file)
{
	int i;
	int start;

	i = 0;
	while (file->ast[i])
	{
		printf("%d %d\n", file->ast[i]->offset, file->header.prog_size);	
		if (file->ast[i]->opcode)
		{
			start = file->ast[i]->offset;
			file->output[start] = file->ast[i]->opcode->opcode;
			if (file->ast[i]->opcode->ocp)
				file->output[start + 1] = create_ocp(file->ast[i]);
			encode_parameters(file, i, start + 2);
		}
		i++;
	}
	return (SUCCESS);
}

t_ex_ret		encode(t_src_file *file)
{
	create_symbol_table(file);
	print_symbol_table(file->symbol_table); // debug
	printf("champ max size %d vs prog_size %d\n", CHAMP_MAX_SIZE, file->header.prog_size);	
	if (file->header.prog_size > CHAMP_MAX_SIZE)
		return (ft_ret_err(CHAMP_TOO_LONG));
	else
		encode_instructions(file);

	return (SUCCESS);
}
