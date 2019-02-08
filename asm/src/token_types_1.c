#include "asm.h"

t_type		get_token_type(char *token_name)
{
	t_type	type;

	type = NONE;
	if (is_whitespace(*token_name))
		type = WHITESPACE;
	if (is_special_char(*token_name))
		type = which_special_char(*token_name);
	if (is_string_char(*token_name))
	{
		type |= STRING;
	}
	return (type);
}

t_bool		is_whitespace(char c)
{
	static const char	*whitespaces = WHITESPACES;

	if ((ft_strchr(whitespaces, c)))
		return (TRUE);
	return (FALSE);
}

t_bool		is_special_char(char c)
{
	static const char	*special_chars = SPECIAL_CHARS;

	if ((ft_strchr(special_chars, c)))
		return (TRUE);
	return (FALSE);
}

t_bool		is_string_char(char c)
{
	static const char	*string_chars = STRING_CHARS;

	if ((ft_strchr(string_chars, c)))
		return (TRUE);
	return (FALSE);
}

t_bool		is_label_char(char c)
{
	static const char	*label_chars = LABEL_CHARS;

	if ((ft_strchr(label_chars, c)))
		return (TRUE);
	return (FALSE);
}
