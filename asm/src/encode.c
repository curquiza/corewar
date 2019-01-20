#include "asm.h"

t_ex_ret		encode_instructions(t_src_file *file)
{
	int i;

	i = 0;
	while (file->ast[i])
	{
		i++;
	}
	return (SUCCESS);
}

t_ex_ret		encode(t_src_file *file)
{
	create_symbol_table(file);
	print_symbol_table(file->symbol_table); // debug
	encode_instructions(file);

	return (SUCCESS);
}
