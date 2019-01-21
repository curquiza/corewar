#include "asm.h"

void			fill_ocp(t_ast *ast, int pos)
{
	if ((ast->arg_type[pos] & T_DIR)== T_DIR)
		ast->ocp |= DIR_CODE << (pos * 2);
	else if ((ast->arg_type[pos] & T_IND) == T_IND)
		ast->ocp |= IND_CODE << (pos * 2);
	else if ((ast->arg_type[pos] & T_REG) == T_REG)
		ast->ocp |= REG_CODE << (pos * 2);
}

unsigned int			create_ocp(t_ast *ast)
{
	int		i;
	
	if (!ast->opcode->ocp)
		return (0);
	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		printf("%s %d", ast->opcode->name, ast->opcode->opcode);	
		fill_ocp(ast, i);
		i++;
	}
	return (ast->ocp);
}

t_ex_ret		encode_instructions(t_src_file *file)
{
	int i;
	int start;

	i = 0;
	while (file->ast[i])
	{
		printf("%d %d", CHAMP_MAX_SIZE, file->ast[i]->offset);	
		start = file->ast[i]->offset;
		file->output[start] = file->ast[i]->opcode->opcode;
		if (file->ast[i]->opcode->ocp)
			file->output[start + 1] = create_ocp(file->ast[i]);
		i++;
	}
	return (SUCCESS);
}

t_ex_ret		encode(t_src_file *file)
{
	create_symbol_table(file);
	// print_symbol_table(file->symbol_table); // debug
	encode_instructions(file);

	return (SUCCESS);
}
