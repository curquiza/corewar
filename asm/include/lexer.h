#ifndef LEXER_H
# define LEXER_H

# define SPECIAL_CHARS 	":,%"
# define WHITESPACES 	" \t\f\n\r\t\v"
# define STRING_CHARS	LABEL_CHARS"-"

typedef enum 			e_type
{
	NONE,
	OPCODE = 2,
	INTEGER = 4,
	REGISTRE = 8,
	LABEL = 16,
	WHITESPACE = 32,
	COLON = 64,
	SEPARATOR = 128,
	DIRECT = 256
}						t_type;

typedef struct			s_token
{
	struct s_token		*prev;
	struct s_token		*next;
	char				*str;
	t_type				type;
	unsigned int		col;
}						t_token;

t_ex_ret				lexer(t_token **tokens, char *line, int nb_line);
t_ex_ret				link_token(t_token **tokens, char *line, int len, t_type type);
void					free_tokens(t_token **tokens);

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
void					print_tokens(t_token *tokens);

#endif
