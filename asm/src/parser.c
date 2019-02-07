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
		ret = list_to_array(list_input, &file->input, ft_lstlen(list_input));
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

	init_parser(file);
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
