/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_stdout_params.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 10:49:28 by sfranc            #+#    #+#             */
/*   Updated: 2019/02/14 10:49:36 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static unsigned int	get_size(t_ast *ast, unsigned int i)
{
	if ((ast->arg_type[i] & T_REG) == T_REG)
		return (NUM_REG_SIZE);
	else if ((ast->arg_type[i] & T_IND) == T_IND)
		return (IND_SIZE);
	else if ((ast->arg_type[i] & T_DIR) == T_DIR)
		return (get_dir_size(ast->opcode->index));
	return (0);
}

static void			print_one_relative_param(int size, int start,
						unsigned char *output)
{
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
}

void				print_relative_params(t_ast *ast, unsigned char *output)
{
	unsigned int	i;
	unsigned int	size;
	unsigned int	start;

	start = ast->offset + 1;
	if (ast->ocp)
		start++;
	i = 0;
	while (i < ast->opcode->param_nb)
	{
		size = get_size(ast, i);
		print_one_relative_param(size, start, output);
		start += size;
		i++;
	}
	ft_putendl("");
}

void				print_raw_params(t_ast *ast, unsigned char *output)
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
	ft_putendl("");
}
