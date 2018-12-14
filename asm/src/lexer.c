#include "asm.h"

/*
** lexer take a line and return a list of tokens.
*/

t_bool				is_whitespace(char c)
{
	static const char 	*whitespaces = WHITESPACES;

	if ((ft_strchr(whitespaces, c)))
		return (TRUE);
	return (FALSE);
}

t_bool				is_special_char(char c)
{
	static const char 	*special_chars = SPECIAL_CHARS;

	if ((ft_strchr(special_chars, c)))
		return (TRUE);
	return (FALSE);
}

t_bool				is_label_char(char c)
{
	static const char 	*label_chars = LABEL_CHARS;

	if ((ft_strchr(label_chars, c)))
		return (TRUE);
	return (FALSE);
}

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
	if (is_label_char(*end))
	{
		while (is_label_char(*end))
			end++;
		return (end - start);
	}
	return (-2);
}


t_ex_ret			lexer(t_token **tokens, char *line, int nb_line)
{
	int		len;
	int		col;
	int		stop;
	t_type	type;

	stop = ft_strlen(line);
	col = 0;
	len = 0;
	while ((col + len) <= stop)
	{
		if ((len = tokenize(line + col)) < 0)
			break ;
		type = get_token_type(line + col, len);
		if ((link_token(tokens, line + col, len, type)) == FAILURE)
			return (FAILURE);
		col += len;
	}
	if (len == -2)
		return (parse_error(nb_line, INVALID_CHAR));
	return (SUCCESS);
}
