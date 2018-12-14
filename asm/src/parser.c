#include "asm.h"

t_ex_ret		parse_line(t_token *tokens)
{
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
		if ((lexer(&tokens, line)) == FAILURE)
			return (FAILURE);
		ft_printf("%d ", nb_line);
		print_tokens(tokens);
		ret = parse_line(tokens); // quit or continue ?
		free_tokens(&tokens);
		ft_strdel(&line);
	}
	return (SUCCESS);
}
