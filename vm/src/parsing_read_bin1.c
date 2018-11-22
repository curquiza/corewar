#include "vm.h"

/*
** Read of prog_size +1 -> to check if the prog is not too big.
*/
t_ex_ret	read_prog(char *filename, int fd, t_player *player)
{
	char	*buff;
	int		read_ret;

	if (!(buff = ft_memalloc(sizeof(char) * (player->header.prog_size + 1))))
		exit_malloc_err();
	read_ret = read(fd, buff, player->header.prog_size + 1);
	if (read_ret == -1)
	{
		ft_strdel(&buff);
		return (read_error(filename));
	}
	if ((unsigned int)read_ret != player->header.prog_size)
	{
		ft_strdel(&buff);
		return (ft_ret_err(PROG_SIZE_ERR));
	}
	if (!(player->prog = ft_strdup(buff)))
	{
		ft_strdel(&buff);
		exit_malloc_err();
	}
	ft_strdel(&buff);
	return (SUCCESS);
}


