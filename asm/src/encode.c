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

t_symbol		*search_symbol_table(t_symbol *symbol_table, char *str)
{
	t_symbol *tmp;

	tmp = symbol_table;
	while (tmp)
	{
		if (ft_strncmp(tmp->label, str, ft_strlen(str)) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}		

t_ex_ret 		get_indirect_label(unsigned char *output, char *label, t_symbol *symbol_table, int offset)
{
	unsigned short	*tmp;
	t_symbol		*label_ptr;

	(void)offset;

	tmp = (unsigned short*)output;
	if ((label_ptr = search_symbol_table(symbol_table, label)) == NULL)
		return (label_not_found(label));
	
	ft_printf("get_indirect_label:%s %d\n", label, (unsigned short)(offset - label_ptr->offset - offset)); // debug
	*tmp = ft_swap_short((unsigned short)(label_ptr->offset - offset)); // big_endian...
	
	return (SUCCESS);
}

void			get_indirect_value(unsigned char *output, char *value)
{
	unsigned short *tmp;

	tmp = (unsigned short*)output;
	ft_printf("get_indirect_value: %d\n", ft_atoi(value)); // debug
	*tmp = (unsigned short)ft_atoi(value);
	return ;
}

void			get_registre(unsigned char *output, char *r)
{
	ft_printf("get_registre: %d\n", ft_atoi(r + 1));
	*output = ft_atoi(r + 1);
	return ;
}

t_ex_ret			encode_parameters(t_src_file *file, int i, int pos)
{
	unsigned int		j;

	j = 0;
	while (j < file->ast[i]->opcode->param_nb)
	{
		if ((file->ast[i]->arg_type[j] & T_REG) == T_REG)
		{
			get_registre(file->output + pos, file->ast[i]->arguments[j]);
			pos += NUM_REG_SIZE;
		}
		if ((file->ast[i]->arg_type[j] & T_IND) == T_IND)
		{
			if ((file->ast[i]->arg_type[j] & T_LAB) == T_LAB)
			{
				if (get_indirect_label(file->output + pos, file->ast[i]->arguments[j], file->symbol_table, file->ast[i]->offset) == FAILURE)
					return (FAILURE);
			}
			else
				get_indirect_value(file->output + pos, file->ast[i]->arguments[j]);
			pos += IND_SIZE;
		}		
		j++;
	}
	return (SUCCESS);
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
			if (encode_parameters(file, i, start + 2) == FAILURE)
				return (FAILURE);
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
