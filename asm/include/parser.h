#ifndef PARSER_H
# define PARSER_H

# include "ast.h"

# define NB_OPCODE		16

t_ex_ret		parse(t_src_file *file);
t_ex_ret		parse_name(t_src_file *file);
t_ex_ret		parse_comment(t_src_file *file);
t_ex_ret		parser(t_src_file *file);
t_ex_ret		parse_line(t_ast *ast, t_token_list *tokens, int nb_line);

t_ex_ret		parse_live(t_ast *ast, t_token_list *tokens, int nb_line);
t_ex_ret		parse_ld(t_ast *ast, t_token_list *tokens, int nb_line);
t_ex_ret		parse_st(t_ast *ast, t_token_list *tokens, int nb_line);
t_ex_ret		parse_add(t_ast *ast, t_token_list *tokens, int nb_line);
t_ex_ret		parse_sub(t_ast *ast, t_token_list *tokens, int nb_line);
t_ex_ret		parse_and(t_ast *ast, t_token_list *tokens, int nb_line);
t_ex_ret		parse_or(t_ast *ast, t_token_list *tokens, int nb_line);
t_ex_ret		parse_xor(t_ast *ast, t_token_list *tokens, int nb_line);
t_ex_ret		parse_zjump(t_ast *ast, t_token_list *tokens, int nb_line);
t_ex_ret		parse_ldi(t_ast *ast, t_token_list *tokens, int nb_line);
t_ex_ret		parse_sti(t_ast *ast, t_token_list *tokens, int nb_line);
t_ex_ret		parse_fork(t_ast *ast, t_token_list *tokens, int nb_line);
t_ex_ret		parse_lld(t_ast *ast, t_token_list *tokens, int nb_line);
t_ex_ret		parse_lldi(t_ast *ast, t_token_list *tokens, int nb_line);
t_ex_ret		parse_lfork(t_ast *ast, t_token_list *tokens, int nb_line);
t_ex_ret		parse_aff(t_ast *ast, t_token_list *tokens, int nb_line);


#endif
