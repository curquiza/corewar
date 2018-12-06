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
	{ 0x02, "ld", 2, { T_DIR | T_IND, T_REG }, 5, TRUE, FALSE, NULL },
	{ 0x03, "st", 2, { T_REG, T_IND | T_REG }, 5, TRUE, FALSE, NULL },
	{ 0x04, "add", 3, { T_REG, T_REG, T_REG }, 10, TRUE, FALSE, NULL },
	{ 0x05, "sub", 3, { T_REG, T_REG, T_REG }, 10, TRUE, FALSE, &op_and },
	{ 0x06, "and", 3, { T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG },
		6, TRUE, FALSE, NULL },
	{ 0x07, "or", 3, { T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG },
		6, TRUE, FALSE, NULL },
	{ 0x08, "xor", 3, { T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG },
		6, TRUE, FALSE, NULL },
	{ 0x09, "zjump", 1, { T_DIR }, 20, FALSE, TRUE, &op_zjump },
	{ 0x0a, "ldi", 3, { T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG },
		25, TRUE, TRUE, NULL },
	{ 0x0b, "sti", 3, { T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG },
		25, TRUE, TRUE, &op_sti },
	{ 0x0c, "fork", 1, { T_DIR }, 800, FALSE, TRUE, NULL },
	{ 0x0d, "lld", 2, { T_DIR | T_IND, T_REG }, 10, TRUE, FALSE, NULL },
	{ 0x0e, "lldi", 3, { T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG },
		50, TRUE, TRUE, NULL },
	{ 0x0f, "lfork", 1, { T_DIR }, 1000, FALSE, TRUE, NULL },
	{ 0x10, "aff", 1, { T_REG }, 2, TRUE, FALSE, NULL }
};

static void	parse_param_without_ocp(t_memcase *mem, t_processus *proc, t_param *params)
{
	if (proc->current_op->index == TRUE)
		params->size = IND_SIZE;
	else
		params->size = DIR_SIZE;
	params->type = T_DIR;
	params->value = memvalue_to_uint32(mem, proc->index + 1, DIR_SIZE);
}

static void	parse_all_params(t_memcase *mem, t_param *params, t_processus *proc)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (i < proc->current_op->param_nb)
	{
		params[i].value = memvalue_to_uint32(mem, proc->index + 2 + j, params[i].size);
		j += params[i].size;
		i++;
	}
}

static void	get_type_and_size(int code, t_param *params, t_op *current_op)
{
	if (code == REG_CODE)
	{
		params->size = NUM_REG_SIZE;
		params->type = T_REG;
	}
	else if (code == DIR_CODE)
	{
		if (current_op->index == TRUE)
			params->size = IND_SIZE;
		else
			params->size = DIR_SIZE;
		params->type = T_DIR;
	}
	else if (code == IND_CODE)
	{
		params->size = IND_SIZE;
		params->type = T_IND;
	}
}

static void	parse_ocp(t_byte memvalue, t_param *params, t_op *current_op)
{
	int		code;
	int		i;

	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		code = (memvalue >> (6 - i * 2)) & OCP_MASQ;
		get_type_and_size(code, &params[i], current_op);
		i++;
	}
}

void	parse_op_params(t_vm *vm, t_processus *proc, t_param *params)
{
	ft_bzero(params, 4 * sizeof(*params));
	if (proc->current_op->ocp == FALSE)
		parse_param_without_ocp(vm->memory, proc, &params[0]);
	else
	{
		parse_ocp(vm->memory[get_mem_index(proc->index + 1)].value, params, proc->current_op);
		parse_all_params(vm->memory, params, proc);
	}
}
