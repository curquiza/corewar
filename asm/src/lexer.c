#include "asm.h"

/*
** lexer take a line and return a list of tokens.
*/

t_bool		is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (TRUE);
	return (FALSE);
}

t_bool		is_special_char(char c)
{
	const char *special_chars = SPECIAL_CHARS;

	if (!(ft_strchr(special_chars, c)))
		return (TRUE);
	return (FALSE);
}

t_bool		is_label_char(char c)
{
	const char *laber_chars = LABEL_CHARS;

	if (!(ft_strchr(laber_chars, c)))
		return (TRUE);
	return (FALSE);
}

int					tokenize(char *start)
{
	static const char 	*label_chars = LABEL_CHARS;
	static const char 	*special_chars = SPECIAL_CHARS;
	static const char 	*whitespaces = WHITESPACES;
	char 	*end;
	
	if (!*start)
		return (-1);
	if (ft_strchr(special_chars, *start))
		return (1);
	end = start;
	if (ft_strchr(whitespaces, *end))
	{
		while (ft_strchr(whitespaces, *end))
			end++;
		return (end - start);
	}
	if (ft_strchr(label_chars, *end))
	{
		while (ft_strchr(label_chars, *end))
			end++;
		return (end - start);
	}
	return (-2);
}


t_ex_ret			lexer(t_token **tokens, char *line)
{
	int		len;
	char	*stop;

	stop = line + ft_strlen(line);
	while (*line)
	{
		ft_printf("ici: %s\t", line);
		if ((len = tokenize(line)) < 0)
			break ;
		ft_printf("len: %d\n", len);
		if ((link_token(tokens, line, len)) == FAILURE)
			return (FAILURE);
		if ((line + len) <= stop)
			line += len;
		else
			break ;
	}
	if (len == -2)
		return (ft_ret_err(INVALID_CHAR));
	return (SUCCESS);
}
