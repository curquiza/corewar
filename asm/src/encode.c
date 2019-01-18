#include "asm.h"

t_ex_ret		encode(t_src_file *file)
{
	(void)file;
	create_symbol_table(file);
	print_symbol_table(file->symbol_table);

	return (SUCCESS);
}
