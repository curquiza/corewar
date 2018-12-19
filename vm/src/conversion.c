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
int32_t	memvalue_to_int32_restrict(t_memcase *vm_mem, t_processus *proc,
								signed short index, int size)
{
	int32_t		rslt;
	int			tmp;

	tmp = get_mem_index(proc, index, RESTRICT);
	rslt = 0;
	if (size >= 1)
		/*rslt |= (t_byte) vm_mem[get_mem_index(proc, index, RESTRICT)].value;*/
		rslt |= (t_byte) vm_mem[tmp].value;
	if (size >= 2)
		/*rslt = (rslt << 8) | (t_byte) vm_mem[get_mem_index(proc, index + 1, RESTRICT)].value;*/
		rslt = (rslt << 8) | (t_byte) vm_mem[(tmp + 1) % MEM_SIZE].value;
	if (size >= 3)
		rslt = (rslt << 8) | (t_byte) vm_mem[(tmp + 2) % MEM_SIZE].value;
	if (size >= 4)
		rslt = (rslt << 8) | (t_byte) vm_mem[(tmp + 3) % MEM_SIZE].value;
	return (rslt);
}

int32_t	memvalue_to_int32_norestrict(t_memcase *vm_mem, t_processus *proc,
								signed short index, int size)
{
	uint32_t		rslt;

	rslt = 0;
	if (size >= 1)
		rslt |= (t_byte) vm_mem[get_mem_index(proc, index, DEF_ADDR)].value;
	if (size >= 2)
		rslt = (rslt << 8) | (t_byte) vm_mem[get_mem_index(proc, index + 1, DEF_ADDR)].value;
	if (size >= 3)
		rslt = (rslt << 8) | (t_byte) vm_mem[get_mem_index(proc, index + 2, DEF_ADDR)].value;
	if (size >= 4)
		rslt = (rslt << 8) | (t_byte) vm_mem[get_mem_index(proc, index + 3, DEF_ADDR)].value;
	return (rslt);
}
