#include "asm.h"

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

t_ex_ret		parse_line(t_token *tokens, int nb_line)
{
	(void)nb_line;
	(void)tokens;

	return (SUCCESS);
}

t_ex_ret		parser(t_src_file *file)
{
	char		*line;
	t_token 	*tokens;
	int			ret;
	int			nb_line;

	tokens = NULL;
	nb_line = file->nb_line;
	while ((get_next_line(file->fd, &line)) > 0)
	{
		nb_line++;
		if ((lexer(&tokens, line, nb_line)) == FAILURE)
			return (FAILURE);
		ft_printf("%d ", nb_line);
		print_tokens(tokens);
		ret = parse_line(tokens, nb_line);
		free_tokens(&tokens);
		ft_strdel(&line);
	}
	return (SUCCESS);
}
