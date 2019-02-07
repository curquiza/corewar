#include "asm.h"

/*
** After having parsed the file, get the size of the file.
*/

static void			fill_prog_size(t_src_file *file)
{
	int i;

	i = 0;
	while (file->ast[i])
	{
		i++;
	}
	file->header.prog_size = file->ast[i - 1] ?
		ft_swap_int(file->ast[i - 1]->offset + file->ast[i - 1]->size) : 0;
}

/*
** COMPILE: Parse, encode and output.
** Everything happens here...
*/

t_ex_ret			compile(t_src_file *file)
{
	if ((parse_name(file)) == FAILURE)
		return (FAILURE);
	if ((parse_comment(file)) == FAILURE)
		return (FAILURE);
	if ((parser(file)) == FAILURE)
		return (FAILURE);
	fill_prog_size(file);
	if (ft_swap_int(file->header.prog_size) > CHAMP_MAX_SIZE)
		return (parse_error(0, CHAMP_TOO_LONG));
	if ((encode(file)) != SUCCESS)
		return (FAILURE);
	if (!(g_flags & FLAG_A))
	{
		if ((write_output_file(file)) == FAILURE)
			return (FAILURE);
	}
	else
		write_output_stdout(file);
	close(file->fd);
	return (SUCCESS);
}

/*
** With the intention of having multithreading (lol), the file was entirely read
** and lines were tranfered into an array.
** No multithreading were finally implemented.
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
	t_token_list	*tokens;
	int				i;
	int				nb_line;

	init_parser(file);
	nb_line = ft_tablen(file->input);
	if ((init_ast_array(&file->ast, nb_line)) == FAILURE)
		return (FAILURE);
	file->nb_line++;
	i = 0;
	while (i < nb_line)
	{
		tokens = NULL;
		if ((lexer(&tokens, file->input[i], i + file->nb_line)) == FAILURE)
		{
			ft_tabdel(&file->input);
			free_tokens(&tokens);
			return (FAILURE);
		}
		if ((ret = parse_instr(file->ast[i], tokens, i + file->nb_line))
			== FAILURE)
		{
			ft_tabdel(&file->input);
			free_tokens(&tokens);
			return (FAILURE);
		}
		fill_offset(file->ast, i);
		free_tokens(&tokens);
		i++;
	}
	ft_tabdel(&file->input);
	return (ret);
}
