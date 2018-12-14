#include "vm.h"

/*
** t_byte	opcode
** char		*name
** int		param_nb
** t_byte	param_type[MAX_ARGS_NUMBER]
** int		cycles
** t_bool	ocp
** t_bool	index
** void		(*op_func)(t_vm *, t_processus *)
*/

t_op g_op[OP_NUMBER] =
{
	{ 0x01, "live", 1, { T_DIR }, 10, FALSE, FALSE, &op_live },
	{ 0x02, "ld", 2, { T_DIR | T_IND, T_REG }, 5, TRUE, FALSE, &op_ld },
	{ 0x03, "st", 2, { T_REG, T_IND | T_REG }, 5, TRUE, FALSE, &op_st },
	{ 0x04, "add", 3, { T_REG, T_REG, T_REG }, 10, TRUE, FALSE, NULL },
	{ 0x05, "sub", 3, { T_REG, T_REG, T_REG }, 10, TRUE, FALSE, NULL },
	{ 0x06, "and", 3, { T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG },
		6, TRUE, FALSE, &op_and },
	{ 0x07, "or", 3, { T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG },
		6, TRUE, FALSE, NULL },
	{ 0x08, "xor", 3, { T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG },
		6, TRUE, FALSE, NULL },
	{ 0x09, "zjmp", 1, { T_DIR }, 20, FALSE, TRUE, &op_zjmp },
	{ 0x0a, "ldi", 3, { T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG },
		25, TRUE, TRUE, NULL },
	{ 0x0b, "sti", 3, { T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG },
		25, TRUE, TRUE, &op_sti },
	{ 0x0c, "fork", 1, { T_DIR }, 800, FALSE, TRUE, &op_fork },
	{ 0x0d, "lld", 2, { T_DIR | T_IND, T_REG }, 10, TRUE, FALSE, NULL },
	{ 0x0e, "lldi", 3, { T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG },
		50, TRUE, TRUE, NULL },
	{ 0x0f, "lfork", 1, { T_DIR }, 1000, FALSE, TRUE, NULL },
	{ 0x10, "aff", 1, { T_REG }, 2, TRUE, FALSE, NULL }
};
