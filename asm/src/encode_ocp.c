#include "asm.h"

static void			fill_ocp(t_ast *ast, int pos)
{
	if ((ast->arg_type[pos] & T_DIR) == T_DIR)
		ast->ocp |= (DIR_CODE << ((3 - pos) * 2));
	else if ((ast->arg_type[pos] & T_IND) == T_IND)
		ast->ocp |= (IND_CODE << ((3 - pos) * 2));
	else if ((ast->arg_type[pos] & T_REG) == T_REG)
		ast->ocp |= (REG_CODE << ((3 - pos) * 2));
}

unsigned char		create_ocp(t_ast *ast)
{
	unsigned int		i;

	if (!ast->opcode->ocp)
		return (0);
	i = 0;
	while (i < ast->opcode->param_nb)
	{
		fill_ocp(ast, i);
		i++;
	}
	return (ast->ocp);
}
