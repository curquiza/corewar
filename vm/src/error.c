#include "vm.h"

void	exit_malloc_err(void)
{
	clean_all();
	ft_dprintf(2, "Malloc error\n");
	exit(FAILURE);
}

t_ex_ret	wrong_flag_err(char *s)
{
	ft_dprintf(2, "Error: %s: %s", s, WRONG_FLAG_ERR);
	return (FAILURE);
}

t_ex_ret	player_num_err(void)
{
	ft_dprintf(2, PLAYER_NUM_ERR);
	return (FAILURE);
}

t_ex_ret	dump_cycle_err(void)
{
	ft_dprintf(2, DUMP_CYCLE_ERR);
	return (FAILURE);
}

t_ex_ret	max_player_err(void)
{
	ft_dprintf(2, MAX_PLAYER_ERR);
	return (FAILURE);
}
