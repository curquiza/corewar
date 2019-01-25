#include "asm.h"

static void			fill_ocp(t_ast *ast, int pos)
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