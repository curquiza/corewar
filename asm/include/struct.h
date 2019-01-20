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

typedef struct					s_ast
{
	char						*label;
	struct s_op 				*opcode;
	char						*arguments[MAX_ARGS_NUMBER];
	t_arg_type					arg_type[MAX_ARGS_NUMBER];	
	int							ocp;
	int							size;
	int							offset;
}								t_ast;

typedef struct					s_symbol
{
	struct s_symbol			*prev;
	struct s_symbol			*next;
	char						*label;
	int							offset;	
}								t_symbol;

typedef struct					s_src_file
{
	int							fd;
	t_header					header;	
	char						*filename;
	int							nb_line;
	t_ast						**ast;
	t_symbol					*symbol_table;
	char						output[CHAMP_MAX_SIZE];
}								t_src_file;

typedef struct					s_op
{
	char						*name;
	unsigned int				param_nb;
	t_arg_type					param_type[MAX_ARGS_NUMBER];
	unsigned char				opcode;
	unsigned char				ocp;
	unsigned char				index;
} 								t_op;

#endif
