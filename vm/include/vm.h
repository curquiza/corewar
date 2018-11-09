#ifndef VM_H
# define VM_H

# include "libft.h"
# include "op.h"

# include <fcntl.h>
# include <stdio.h>

typedef		uint32_t t_exit;
typedef		unsigned char byte_t;

typedef struct	s_memcase
{
	char	value;
	char	*color;
}				t_memcase;

typedef struct 	s_vm
{
	t_memcase	memory[MEM_SIZE];
}				t_vm;

#endif
