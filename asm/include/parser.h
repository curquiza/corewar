#ifndef PARSER_H
# define PARSER_H

# define NB_OPCODE				16

typedef struct					s_src_file
{
	int							fd;
	t_header					header;	
	char						*filename;
	int							nb_line;
}								t_src_file;

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

typedef struct 					s_label
{
	t_token 					*label;
}								t_label;

typedef struct 					s_instr
{
	t_op 						*opcode;
	t_token 					*arguments;
}								t_instr;

typedef struct					s_line
{
	t_label						*label;
	t_instr						*instr;
	int							size;
	int							offset;
}								t_line;

extern t_op 					g_op_tab[17];

t_ex_ret        				parse(t_src_file *file);
t_ex_ret        				parse_name(t_src_file *file);
t_ex_ret        				parse_comment(t_src_file *file);
t_ex_ret						parser(t_src_file *file);
t_ex_ret     					parse_error(int line, char *message);

#endif
