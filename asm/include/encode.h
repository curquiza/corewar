#ifndef ENCODE_H
# define ENCODE_H

t_ex_ret		encode(t_src_file *file);

t_ex_ret		create_symbol_table(t_src_file *file);
void			free_symbol_table(t_symbol **symbols);

unsigned char	create_ocp(t_ast *ast);
t_ex_ret		get_indirect(t_src_file *file, int i, int j, int pos);
t_ex_ret		get_direct(t_src_file *file, int i, int j, int pos);

t_symbol		*search_symbol_table(t_symbol *symbol_table, char *str);
t_ex_ret		label_not_found(char *label);

unsigned int	ft_swap_int(unsigned int n);
unsigned short	ft_swap_short(unsigned short n);

#endif
