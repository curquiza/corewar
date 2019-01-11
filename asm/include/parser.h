#ifndef PARSER_H
# define PARSER_H

# include "ast.h"

# define NB_OPCODE				16

t_ex_ret		parse(t_src_file *file);
t_ex_ret		parse_name(t_src_file *file);
t_ex_ret		parse_comment(t_src_file *file);
t_ex_ret		parser(t_src_file *file);
t_ex_ret		parse_line(t_ast *ast, t_token_list *tokens, int nb_line);
t_ex_ret     	parse_error(int line, char *message);

#endif
