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

t_ex_ret		parse_line(t_token_list *tokens, int nb_line)
{
	(void)nb_line;
	(void)tokens;

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
		ret = list_to_array(list_input, array_input, ft_lstlen(list_input));
	ft_lstdel(&list_input, &del);
	return (ret);
}

t_ex_ret		new_lines_array(t_line ***lines, int nb_line)
{
	if (!(*lines = (t_line**)malloc(sizeof(t_line) * (nb_line + 1))))
		return (ft_ret_err(ERR_MALLOC));
	(*lines)[nb_line] = 0;
	return (SUCCESS);
}

t_ex_ret		parser(t_src_file *file)
{
	t_ex_ret		ret;
	char			**array_input;
	t_token_list 	*tokens;
	int 			i;
	int 			nb_line;
	t_line			**lines;

	array_input = NULL;
	tokens = NULL;
	lines = NULL;
	init_parser(file, &array_input);
	nb_line = ft_tablen(array_input);
	if ((new_lines_array(&lines, nb_line)) == FAILURE)
		return (FAILURE);
	i = 0;
	while (i < nb_line)
	{
		file->nb_line++;
		if ((lexer(&tokens, array_input[i], file->nb_line)) == FAILURE)
		{
			ft_tabdel(&array_input);
			free_tokens(&tokens);
			return (FAILURE);
		}
		print_tokens(tokens);
		ret = parse_line(tokens, file->nb_line); // return ??
		free_tokens(&tokens);
		i++;
	}
	ft_tabdel(&array_input);
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
