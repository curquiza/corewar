#include "vm.h"

uint32_t	str_to_uint32(char *str)
{
	uint32_t		rslt;

	rslt = 0;
	rslt = (rslt | (t_byte)str[0]) << 8;
	rslt = (rslt | (t_byte)str[1]) << 8;
	rslt = (rslt | (t_byte)str[2]) << 8;
	rslt |= (t_byte)str[3];
	return (rslt);
}

/*
** /!\ Address restriction
*/
uint32_t	memvalue_to_uint32(t_memcase *vm_mem, t_processus *proc,
								signed short index, int size)
{
	uint32_t		rslt;

	rslt = 0;
	if (size >= 1)
		rslt |= (t_byte) vm_mem[get_mem_index(proc, index, RESTRICT)].value;
	if (size >= 2)
		rslt = (rslt << 8) | (t_byte) vm_mem[get_mem_index(proc, index + 1, RESTRICT)].value;
	if (size >= 3)
		rslt = (rslt << 8) | (t_byte) vm_mem[get_mem_index(proc, index + 2, RESTRICT)].value;
	if (size >= 4)
		rslt = (rslt << 8) | (t_byte) vm_mem[get_mem_index(proc, index + 3, RESTRICT)].value;
	return (rslt);
}
