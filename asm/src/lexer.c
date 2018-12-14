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


t_ex_ret			lexer(t_token **tokens, char *line)
{
	int			len;
	int			stop;

	stop = ft_strlen(line) + 1;
	len = 0;
	while (stop--)
	{
		len++;
		if (stop == 0)
		{
			link_token(tokens, line, len);
		}
	}
	return (SUCCESS);
}
