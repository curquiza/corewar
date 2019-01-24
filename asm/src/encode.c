#include "asm.h"

void			get_registre(unsigned char *output, char *r)
{
	ft_printf("get_registre: %d\n", ft_atoi(r + 1));
	*output = ft_atoi(r + 1);
	return ;
}

t_ex_ret		encode_parameters(t_src_file *file, int i, int pos)
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
			if (get_indirect(file, i, j, pos) == FAILURE)
				return (FAILURE);
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
		printf("%d %d\n", file->ast[i]->offset, ft_swap_int(file->header.prog_size));
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
	
	if (encode_instructions(file) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
