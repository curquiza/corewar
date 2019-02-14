/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 10:43:05 by sfranc            #+#    #+#             */
/*   Updated: 2019/02/14 10:43:32 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_ex_ret		init_ast_array(t_ast ***ast, int nb_line)
{
	int		i;

	if (!(*ast = (t_ast**)ft_memalloc(sizeof(t_ast*) * (nb_line + 1))))
		return (ft_ret_err(ERR_MALLOC));
	i = 0;
	while (i < nb_line)
	{
		if (!((*ast)[i] = (t_ast*)ft_memalloc(sizeof(t_ast))))
			return (ft_ret_err(ERR_MALLOC));
		i++;
	}
	return (SUCCESS);
}

void			free_arguments(char *arguments[MAX_ARGS_NUMBER])
{
	int i;

	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		ft_strdel(&arguments[i]);
		i++;
	}
}

void			free_ast_array(t_ast ***ast)
{
	int		i;

	if (!*ast)
		return ;
	i = 0;
	while ((*ast)[i])
	{
		ft_strdel(&((*ast)[i])->label);
		free_arguments((*ast)[i]->arguments);
		free((*ast)[i]);
		i++;
	}
	free(*ast);
	*ast = NULL;
}
