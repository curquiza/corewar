#ifndef LEXER_H
# define LEXER_H

# define SPECIAL_CHARS 	":,%"
# define WHITESPACES 	" \t\f\n\r\t\v"
# define STRING_CHARS	LABEL_CHARS"-"

typedef enum 			e_type
{
	NONE,
	STRING = 1,
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
	char				*str;
	t_type				type;
	unsigned int		line;
	unsigned int		col;
}						t_token;

typedef struct			s_token_list
{
	struct s_token_list		*prev;
	struct s_token_list		*next;
	struct s_token			*token;
}						t_token_list;

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
