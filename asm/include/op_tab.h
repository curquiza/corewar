#ifndef OP_TAB_H
# define OP_TAB_H

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

#endif