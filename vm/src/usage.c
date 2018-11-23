#include "vm.h"

static void	print_usage_line(char *flag, char *description)
{
	ft_printf("   | %-10s %s\n", flag, description);
}

static void	print_usage(void)
{
	ft_printf("Usage : ./corewar [-dump N] [-zaz] [-n N <champion>] <champion> ... \n");
	print_usage_line("dump N", "dumps memory after N cycles then exits, where N is int gte 0");
	print_usage_line("n N", "force champion's number to N, where N is int gte 0");
	print_usage_line("zaz", "display like zaz VM (line of 64 bytes)");
}

t_ex_ret	usage_ret_err(void)
{
	print_usage();
	return (FAILURE);
}
