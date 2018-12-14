#ifndef LEXER_H
# define LEXER_H

# define SPECIAL_CHARS 	":,%"
# define WHITESPACES 	" \t\f\n\r\t\v"

typedef enum 			e_type
{
	NONE,
	STRING = 1,	
	OPCODE = 2,
	INTEGER = 4,
	REGISTRE = 8,
	WHITESPACE = 16,
	COLON = 32,
	SEPARATOR = 64,
	DIRECT = 128
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

/*
** TOKENS
*/
t_ex_ret				link_token(t_token **tokens, char *line, int len, t_type type);
t_ex_ret				create_token(t_token **elem, char *line, int len, t_type type);
void					add_token(t_token **tokens, t_token *new);
void					print_tokens(t_token *tokens);
void					free_tokens(t_token **tokens);

/*
** TOOLS
*/
t_bool					is_whitespace(char c);
t_bool					is_special_char(char c);
t_bool					is_label_char(char c);
t_type 					get_token_type(char *str, int len);
void					print_token_type(t_type type);

#endif
