#include "vm.h"

static void	parse_param_without_ocp(t_memcase *mem, t_processus *proc, t_param *params)
{
	if (proc->current_op->index == TRUE)
		params->size = IND_SIZE;
	else
		params->size = DIR_SIZE;
	params->type = T_DIR;
	params->value = memvalue_to_uint32(mem, proc->pc + 1, DIR_SIZE);
}

static void	parse_all_params(t_memcase *mem, t_param *params, t_processus *proc)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (i < proc->current_op->param_nb)
	{
		params[i].value = memvalue_to_uint32(mem, proc->pc + 2 + j, params[i].size);
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

static t_bool	parse_ocp(t_byte memvalue, t_param *params, t_op *current_op)
{
	int		code;
	int		i;
	t_bool	valid_ocp;

	i = 0;
	valid_ocp = TRUE;
	while (i < current_op->param_nb)
	{
		code = (memvalue >> (6 - i * 2)) & OCP_MASQ;
		get_type_and_size(code, &params[i], current_op);
		if ((params[i].type & current_op->param_type[i]) != params[i].type)
			valid_ocp = FALSE;
		i++;
	}
	return (valid_ocp);
}

t_bool	parse_op_params(t_vm *vm, t_processus *proc, t_param *params)
{
	ft_bzero(params, 4 * sizeof(*params));
	if (proc->current_op->ocp == FALSE)
		parse_param_without_ocp(vm->memory, proc, &params[0]);
	else
	{
		if (parse_ocp(vm->memory[get_mem_index(proc->pc + 1)].value,
						params, proc->current_op) == FALSE)
				return (FALSE);
		parse_all_params(vm->memory, params, proc);
	}
	return (TRUE);
}
