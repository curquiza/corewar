#ifndef LEXER_H
# define LEXER_H

# define SPECIAL_CHARS 	":,%"
# define WHITESPACES 	" \t\f\n\r\t\v"
# define STRING_CHARS	LABEL_CHARS"-"

t_ex_ret				lexer(t_token_list **tokens, char *line, int nb_line);
t_ex_ret				link_token(t_token_list **tokens, char **token_name, int line, int col);
void					free_tokens(t_token_list **tokens);

/*
** TOKEN TYPES
*/
t_bool					is_whitespace(char c);
t_bool					is_special_char(char c);
t_bool					is_string_char(char c);
t_bool					is_label_char(char c);
t_bool					is_label_string(char *str);
t_bool					is_opcode(char *str);
t_bool					is_registre(char *str);
t_type 					which_special_char(char c);

/*
** PRINT LEXER
*/
void					print_tokens(t_token_list *tokens);

#endif
