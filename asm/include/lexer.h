/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 10:42:06 by sfranc            #+#    #+#             */
/*   Updated: 2019/02/14 10:42:52 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define SPECIAL_CHARS 	":,%"
# define WHITESPACES 	" \t\f\n\r\t\v"
# define STRING_CHARS	LABEL_CHARS"-"

t_ex_ret				lexer(t_token_list **tokens, char *line, int nb_line);
t_type					get_token_type(char *token_name);
t_ex_ret				link_token(t_token_list **tokens, char **token_name,
							int line, int col);
void					free_tokens(t_token_list **tokens);

/*
** TOKEN TYPES
*/
t_bool					is_whitespace(char c);
t_bool					is_special_char(char c);
t_bool					is_string_char(char c);
t_bool					is_label_char(char c);
t_bool					is_label_string(char *str);
t_bool					is_registre(char *str);
t_type					which_special_char(char c);
int						is_opcode(char *str);

#endif
