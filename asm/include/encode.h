#ifndef ENCODE_H
# define ENCODE_H

t_ex_ret		encode(t_src_file *file);
t_ex_ret		create_symbol_table(t_src_file *file);
void			free_symbol_table(t_symbol **symbols);

void			print_symbol_table(t_symbol *symbols);

#endif
