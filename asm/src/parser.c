#include "asm.h"

/*
** parse: organize parsing of the name, comment, and instructions.
*/

t_ex_ret		parse(t_src_file *file)
{
	if ((parse_name(file)) == FAILURE)
		return (FAILURE);
	if ((parse_comment(file)) == FAILURE)
		return (FAILURE);
	if ((parser(file)) == FAILURE)
		return (FAILURE);
	
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
** parser: read the end of the file, line by line and parse them.
*/

t_ex_ret		init_parser(t_src_file *file, char ***array_input)
{
	t_ex_ret		ret;
	t_list 			*list_input;

	list_input = NULL;
	ret = FAILURE;
	if ((read_file(file, &list_input)) == SUCCESS)
	{
		// ft_printf("File: "); // debug
		// print_file(list_input); // debug
		ret = list_to_array(list_input, array_input, ft_lstlen(list_input)); // stocker list len.	
	}
	ft_lstdel(&list_input, &del);
	return (ret);
}

void			fill_offset(t_ast **ast, int i)
{
	if (ast[i + 1])
		(ast[i + 1])->offset = (ast[i])->offset + (ast[i])->size;
}

t_ex_ret		parser(t_src_file *file)
{
	t_ex_ret		ret;
	char			**array_input; // struc globale
	t_token_list 	*tokens;
	int 			i;
	int 			nb_line; // suppr

	array_input = NULL;  // struc globale
	init_parser(file, &array_input); // struc globale
	nb_line = ft_tablen(array_input); // optimization ?
	if ((init_ast_array(&file->ast, nb_line)) == FAILURE)
		return (FAILURE);
	file->nb_line++;
	i = 0;
	while (i < nb_line)
	{
		tokens = NULL;
		if ((lexer(&tokens, array_input[i], i + file->nb_line)) == FAILURE)
		{
			ft_tabdel(&array_input);
			free_tokens(&tokens);
			return (FAILURE);
		}
		// print_tokens(tokens); // debug
		if ((ret = parse_line(file->ast[i], tokens, i + file->nb_line)) == FAILURE)
		{
			ft_tabdel(&array_input);
			free_tokens(&tokens);
			// free ast
			return (FAILURE);
		}
		// print_one_ast(file->ast[i]);
		fill_offset(file->ast, i);
		free_tokens(&tokens);
		i++;
	}
	// print_ast_array(file->ast); // debug
	ft_tabdel(&array_input);
	file->header.prog_size = file->ast[i - 1] ? file->ast[i - 1]->offset + file->ast[i - 1]->size : 0;
	return (ret);
}

// t_ex_ret		parser(t_src_file *file)
// {
// 	char			*line;
// 	t_token_list 	*tokens;
// 	t_ex_ret		ret;

// 	tokens = NULL;
// 	while ((get_next_line(file->fd, &line)) > 0)
// 	{
// 		file->nb_line++;
// 		if ((lexer(&tokens, line, file->nb_line)) == FAILURE)
// 			return (FAILURE);
// 		ft_printf("%d ", file->nb_line);
// 		print_tokens(tokens);
// 		ret = parse_line(tokens, file->nb_line);
// 		free_tokens(&tokens);
// 		ft_strdel(&line);
// 	}
// 	return (ret);
// }
