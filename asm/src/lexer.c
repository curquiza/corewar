#include "asm.h"

/*
** lexer take a line and return a list of tokens.
*/

static t_type 			get_token_type(char *str, int len)
{
	t_type	type;
	char	*tmp;

	type = NONE;
	tmp = ft_strsub(str, 0, len);
	if (is_whitespace(*tmp))
		type = WHITESPACE;
	if (is_special_char(*tmp))
		type = which_special_char(*tmp);
	if (is_string_char(*tmp))
	{
		if (ft_is_int(tmp))
			type |= INTEGER;
		if (is_registre(tmp))
			type |= REGISTRE;
		if (is_opcode(tmp))
			type |= OPCODE;
		if (is_label_string(tmp))
			type |= LABEL;
	}
	free(tmp);
	return (type);
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
	if (is_string_char(*end))
	{
		while (is_string_char(*end))
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
