/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 10:48:13 by sfranc            #+#    #+#             */
/*   Updated: 2019/02/14 10:48:20 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_ex_ret				parse_parameters(t_ast *ast, t_token_list **tokens,
							int nb_line)
{
	unsigned int i;

	i = 0;
	while (i < ast->opcode->param_nb)
	{
		if (apply_parse_param(ast->opcode->param_type[i], ast, tokens, i)
			== FAILURE)
			return (parse_error(nb_line, INVALID_PARAM));
		i++;
		if (!(*tokens = skip_whitespaces(*tokens)))
			break ;
		if ((*tokens)->token->type == SEPARATOR)
		{
			*tokens = (*tokens)->next;
			*tokens = skip_whitespaces(*tokens);
		}
		else
			break ;
	}
	if (i != ast->opcode->param_nb)
		return (parse_error(nb_line, INVALID_TOKEN));
	return (SUCCESS);
}

static t_token_list		*move_tokens(t_token_list *tokens, int move)
{
	while (move--)
		tokens = tokens->next;
	return (tokens);
}

t_ex_ret				apply_parse_param(t_arg_type param, t_ast *ast,
							t_token_list **tokens, int pos)
{
	int ret;

	if (((param & T_REG) == T_REG)\
		&& ((ret = parse_registre(ast, *tokens, pos)) != -1))
	{
		*tokens = move_tokens(*tokens, ret);
		return (SUCCESS);
	}
	if (((param & T_DIR) == T_DIR)\
		&& ((ret = parse_direct(ast, *tokens, pos)) != -1))
	{
		*tokens = move_tokens(*tokens, ret);
		return (SUCCESS);
	}
	if (((param & T_IND) == T_IND)\
		&& ((ret = parse_indirect(ast, *tokens, pos)) != -1))
	{
		*tokens = move_tokens(*tokens, ret);
		return (SUCCESS);
	}
	return (FAILURE);
}
