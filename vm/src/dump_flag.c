#include "vm.h"

static int		bytes_per_line(t_vm *vm)
{
	if (flag_is_applied(ZAZ_FLAG, vm) == TRUE)
		return (BYTES_PER_LINE_64);
	return (BYTES_PER_LINE_32);
}

static void	handle_newline(int i, t_vm *vm)
{
	int		b_per_line;

	b_per_line = i % bytes_per_line(vm);
	if (b_per_line == bytes_per_line(vm) - 1)
	{
		flag_is_applied(ZAZ_FLAG, vm)? ft_putchar_fd(' ', vm->trace_fd) : 0;
		ft_putchar_fd('\n', vm->trace_fd);
	}
	else
		ft_putchar_fd(' ', vm->trace_fd);
}

static void	print_mem_addr(int i, t_vm *vm)
{
	if (i % bytes_per_line(vm) == 0)
		ft_dprintf(vm->trace_fd, "0x%0.4x : ", i);
}

void	dump_memory(t_vm *vm)
{
	int			i;
	t_memcase	*memory;

	ft_dprintf(vm->trace_fd, "Dump memory : end of cycle %d\n", vm->dump_cycle);
	memory = vm->memory;
	i = 0;
	while (i < MEM_SIZE)
	{
		print_mem_addr(i, vm);
		if (flag_is_applied(ZAZ_FLAG, vm) == TRUE)
			ft_dprintf(vm->trace_fd, "%0.2x", (t_byte) memory[i].value);
		else
			ft_dprintf(vm->trace_fd, "%s%0.2x%s", memory[i].color,
					(t_byte) memory[i].value, DEF);
		handle_newline(i, vm);
		i++;
	}
}
