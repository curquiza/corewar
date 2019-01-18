#ifndef PARSER_H
# define PARSER_H

# include "ast.h"

# define NB_OPCODE		16
# define NUM_REG_SIZE	1
# define NUM_INDEX_SIZE	2
# define NUM_OP_SIZE	1

t_ex_ret		parse(t_src_file *file);
t_ex_ret		parse_name(t_src_file *file);
t_ex_ret		parse_comment(t_src_file *file);
t_ex_ret		parser(t_src_file *file);
t_ex_ret		parse_line(t_ast *ast, t_token_list *tokens, int nb_line);

t_ex_ret		parse_parameters(t_ast *ast, t_token_list **tokens, int nb_line);

t_token_list	*skip_whitespaces(t_token_list *tokens);
int				parse_direct(t_ast *ast, t_token_list *tokens, int pos);
int				parse_indirect(t_ast *ast, t_token_list *tokens, int pos);
int				parse_registre(t_ast *ast, t_token_list *tokens, int pos);
t_ex_ret		apply_parse_param(t_arg_type param, t_ast *ast, t_token_list **tokens, int pos);

#endif
