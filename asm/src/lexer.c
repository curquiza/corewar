#include "asm.h"

static int			tokenize(char *start)
{
	char 				*end;
	
	if (!*start || *start == COMMENT_CHAR)
		return (-1);
	if (is_special_char(*start))
		return (1);
	end = start;
	if (is_whitespace(*end))
	{
		while (is_whitespace(*end))
			end++;
		return (end - start);
	}
	if (is_string_char(*end))
	{
		while (is_string_char(*end))
			end++;
		return (end - start);
	}
	return (-2);
}

/*
** lexer: take a line and return a list of tokens.
*/

t_ex_ret			lexer(t_token **tokens, char *line, int nb_line)
{
	int		len;
	int		col;
	int		stop;
	char	*token_name;

	stop = ft_strlen(line);
	col = 0;
	len = 0;
	while ((col + len) <= stop)
	{
		if ((len = tokenize(line + col)) < 0)
			break ;
		token_name = ft_strsub(line, col, len);
		// type = get_token_type(token_name);
		// free(token_name);
		if ((link_token(tokens, &token_name, nb_line, col)) == FAILURE)
			return (FAILURE);
		col += len;
	}
	if (len == -2)
		return (parse_error(nb_line, INVALID_CHAR));
	return (SUCCESS);
}
