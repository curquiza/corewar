#ifndef AST_H
# define AST_H

typedef struct 					s_label
{
	t_token_list 				*label;
}								t_label;

typedef struct 					s_instr
{
	t_op 						*opcode;
	t_token_list				*arguments;
}								t_instr;

typedef struct					s_ast
{
	t_label						*label;
	t_instr						*instr;
	int							size;
	int							offset;
}								t_ast;

t_ex_ret						init_ast_array(t_ast ***ast, int nb_line);
void							free_ast_array(t_ast ***ast);

t_ex_ret						init_label(t_label **label, t_token_list *tokens);
void							free_label(t_label **label);

void							print_ast_array(t_ast **ast);

#endif
