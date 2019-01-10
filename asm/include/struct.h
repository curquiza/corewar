#ifndef STRUCT_H
# define STRUCT_H

typedef enum 					e_type
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
}								t_type;

typedef struct					s_token
{
	char						*str;
	t_type						type;
	unsigned int				line;
	unsigned int				col;
}								t_token;

typedef struct					s_token_list
{
	struct s_token_list			*prev;
	struct s_token_list			*next;
	struct s_token				*token;
}								t_token_list;

typedef struct					s_op
{
	char						*name;
	unsigned char				nb_arg;
	t_arg_type					args[3];
	unsigned char				opcode;
	unsigned int				nb_cycle;
	char						*desc;
	unsigned char				octal;
	unsigned char				label;
} 								t_op;

typedef struct					s_ast
{
	t_token_list				*label;
	t_op 						*opcode;
	t_token_list				*arguments;
	int							size;
	int							offset;
}								t_ast;

typedef struct					s_src_file
{
	int							fd;
	t_header					header;	
	char						*filename;
	int							nb_line;
	t_ast						**ast;
}								t_src_file;

#endif

