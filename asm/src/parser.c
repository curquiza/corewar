/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 10:48:16 by sfranc            #+#    #+#             */
/*   Updated: 2019/02/14 10:48:20 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** With the intention of having multithreading (lol), the file was entirely read
** and lines were tranfered into an array.
** No multithreading were finally implemented.
** Also in this function, some init steps...
*/

static t_ex_ret		init_parser(t_src_file *file)
{
	t_ex_ret		ret;
	t_list			*list_input;

	list_input = NULL;
	ret = FAILURE;
	if ((read_file(file, &list_input)) == SUCCESS)
	{
		if ((ret = list_to_array(list_input, &file->input,
			ft_lstlen(list_input))) == FAILURE)
		{
			return (parse_error(file->nb_line, NO_INSTR));
		}
	}
	else
		return (parse_error(file->nb_line, NO_INSTR));
	ft_lstdel(&list_input, &del);
	file->nb_instr = ft_tablen(file->input);
	if ((init_ast_array(&file->ast, file->nb_instr)) == FAILURE)
		return (FAILURE);
	return (ret);
}

/*
** Each "ast" (= line of instruction) gives its offset + size to the next.
*/

static void			fill_offset(t_ast **ast, int i)
{
	if (ast[i + 1])
		(ast[i + 1])->offset = (ast[i])->offset + (ast[i])->size;
}

/*
** PARSER: A while on an array of lines, lexing and parsing lines by lines.
** the parser fills an ast, a structure with 3 data:
** label, opcode and arguments.
*/

t_ex_ret			parser(t_src_file *file)
{
	t_ex_ret		ret;
	int				i;

	if (init_parser(file) == FAILURE)
		return (FAILURE);
	file->nb_line++;
	i = 0;
	while (i < file->nb_instr)
	{
		file->tokens = NULL;
		if ((lexer(&file->tokens, file->input[i], i + file->nb_line))
			== FAILURE)
		{
			return (FAILURE);
		}
		if ((ret = parse_instr(file->ast[i], file->tokens, i + file->nb_line))
			== FAILURE)
		{
			return (FAILURE);
		}
		fill_offset(file->ast, i);
		free_tokens(&file->tokens);
		i++;
	}
	return (ret);
}
