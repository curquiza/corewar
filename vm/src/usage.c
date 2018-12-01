#include "vm.h"

static void	print_usage_line(char *flag, char *description)
{
	ft_printf("   | %-20s %s\n", flag, description);
}

static void	print_usage(void)
{
	ft_printf("Usage : ./corewar [-dump N] [-zaz] [-visual] [-verbose 1|2] [-n N <champion>] <champion> ... \n");
	print_usage_line("dump N", "dumps memory after N cycles then exits, where N is int >= 0");
	print_usage_line("zaz", "displays like zaz VM (line of 64 bytes) for dump flag");
	print_usage_line("n N", "forces champion's number to N, where N is int >= 0");
	print_usage_line("visual", "displays a Ncurses visual");
	print_usage_line("verbose", "verbose mode (1 : basic | 2 : all)");
}

t_ex_ret	usage_ret_err(void)
{
	print_usage();
	return (FAILURE);
}
