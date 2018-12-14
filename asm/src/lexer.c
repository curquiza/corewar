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
	const char 	*label_chars = LABEL_CHARS;
	const char 	*special_chars = SPECIAL_CHARS;
	const char 	*whitespaces = " \t";
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

	while (*end++)
	{
		if (!*end || (ft_strchr(whitespaces, *end) || (ft_strchr(special_chars, *end))))
			return (end - start);
	}
	return (-2);
}


t_ex_ret			lexer(t_token **tokens, char *line)
{


	int			len;
	int			stop;


	ft_printf("lexer!");

	stop = ft_strlen(line);
	while (stop--)
	{
		ft_printf("ici: %s\t", line);
		if ((len = tokenize(line, special_chars, whitespaces)) < 0)
			break ;
		ft_printf("len: %d\n", len);
		link_token(tokens, line, len);
		line += len;
		stop -= len;
	}
	print_tokens(*tokens);
	return (SUCCESS);
}
