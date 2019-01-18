#ifndef AST_H
# define AST_H

t_ex_ret		init_ast_array(t_ast ***ast, int nb_line);
void			free_ast_array(t_ast ***ast);

void			print_one_ast(t_ast *ast);
void			print_ast_array(t_ast **ast);

#endif
