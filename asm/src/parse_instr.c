/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 10:48:10 by sfranc            #+#    #+#             */
/*   Updated: 2019/02/14 10:48:20 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_token_list		*skip_whitespaces(t_token_list *tokens)
{
	t_token_list	*current;

	if (!tokens)
		return (NULL);
	current = tokens;
	while (current)
	{
		if (current->token->type == WHITESPACE)
			current = current->next;
		else
			break ;
	}
	return (current);
}

static t_ex_ret		parse_label(t_ast *ast, t_token_list **tokens, int nb_line)
{
	if (!(*tokens = skip_whitespaces(*tokens)))
		return (SUCCESS);
	if ((*tokens)->token->type != STRING)
		return (parse_error_token(nb_line,
			(*tokens)->token->str, INVALID_TOKEN));
	else if (((*tokens)->token->type == STRING)
		&& is_label_string((*tokens)->token->str)
		&& (*tokens)->next
		&& ((*tokens)->next->token->type == COLON))
	{
		ast->label = ft_strdup((*tokens)->token->str);
		*tokens = (*tokens)->next->next ? (*tokens)->next->next : NULL;
	}
	return (SUCCESS);
}

static t_ex_ret		parse_opcode(t_ast *ast, t_token_list **tokens, int nb_line)
{
	int		nb;

	if (!(*tokens = skip_whitespaces(*tokens)))
		return (SUCCESS);
	if ((*tokens)->token->type != STRING)
		return (parse_error_token(nb_line,
			(*tokens)->token->str, INVALID_TOKEN));
	else if ((nb = is_opcode((*tokens)->token->str)) != -1)
	{
		ast->opcode = &g_op_tab[nb];
		ast->size += 1;
		if (ast->opcode->ocp)
			ast->size += NUM_OP_SIZE;
		*tokens = (*tokens)->next ? (*tokens)->next : NULL;
		return (SUCCESS);
	}
	return (parse_error_token(nb_line, (*tokens)->token->str, INVALID_OPCODE));
}

static t_ex_ret		parse_arguments(t_ast *ast, t_token_list **tokens,
						int nb_line)
{
	*tokens = skip_whitespaces(*tokens);
	if (!*tokens && ast->opcode)
		return (parse_error_token(nb_line, ast->opcode->name, NB_PARAMS));
	else if (!*tokens)
		return (SUCCESS);
	if (parse_parameters(ast, tokens, nb_line) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

/*
** PARSE_INSTR: every instruction is a line with an optionnal label, an opcode,
** and some parameters (also named arguments).
*/

t_ex_ret			parse_instr(t_ast *ast, t_token_list *tokens, int nb_line)
{
	t_token_list *current_token;

	if (!tokens)
		return (SUCCESS);
	current_token = tokens;
	if ((parse_label(ast, &current_token, nb_line)) == FAILURE)
		return (FAILURE);
	if ((parse_opcode(ast, &current_token, nb_line)) == FAILURE)
		return (FAILURE);
	if ((parse_arguments(ast, &current_token, nb_line)) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
