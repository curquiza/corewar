/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 10:44:24 by sfranc            #+#    #+#             */
/*   Updated: 2019/02/14 10:44:26 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** TOKENIZE: the rules to cut a string into words.
*/

static int			tokenize(char *start)
{
	char	*end;

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
** LEXER: take a line and return a list of tokens.
*/

t_ex_ret			lexer(t_token_list **tokens, char *line, int nb_line)
{
	int		len;
	int		col;
	int		stop;
	char	*token_name;

	stop = ft_strlen(line);
	col = 0;
	len = 0;
	while (col <= stop)
	{
		if ((len = tokenize(line + col)) < 0)
			break ;
		token_name = ft_strsub(line, col, len);
		if ((link_token(tokens, &token_name, nb_line, col)) == FAILURE)
			return (FAILURE);
		col += len;
	}
	if (len == -2)
		return (parse_error(nb_line, INVALID_CHAR));
	return (SUCCESS);
}
