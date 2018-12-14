#ifndef PARSER_H
# define PARSER_H

# define NB_OPCODE				16

typedef struct					s_src_file
{
	int							fd;
	t_header					header;	
	char						*filename;
	t_token						*tokens;
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

extern t_op 					g_op_tab[17];

t_ex_ret						parser(t_src_file *file);

#endif
