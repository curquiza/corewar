#ifndef LEXER_H
# define LEXER_H

# define SPECIAL_CHARS 	"#:,%+-"
# define WHITESPACES 	" \t\f\n\r\t\v"

typedef enum e_type
{
	INVALID,
	WHITESPACE,
	NEWLINE,
	OPCODE,
	STRING,
	VALUE,
	REGISTRE,
	SPECIAL
}				t_type;

typedef struct	s_token
{
	struct s_token		*prev;
	struct s_token		*next;
	char				*str;
	t_type				type;
	unsigned int		col;
}				t_token;

// t_token			*lexer(char *line);
t_ex_ret			lexer(t_token **tokens, char *line);

/*
** TOKENS
*/
t_ex_ret		link_token(t_token **tokens, char *line, int len);
t_ex_ret		create_token(t_token **elem, char *line, int len);
void			add_token(t_token **tokens, t_token *new);
// void			remove_current_token(t_src_file *file);
void			print_tokens(t_token *tokens);
void			print_rev_tokens(t_token *tokens);
void			free_tokens(t_token **tokens);


#endif
