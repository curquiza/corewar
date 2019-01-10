/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_read_bin1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 10:51:42 by curquiza          #+#    #+#             */
/*   Updated: 2019/01/10 11:00:47 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_ex_ret	handle_read_prog_err(int read_ret, char *filename,
									unsigned int prog_size)
{
	if (read_ret == -1)
		return (read_error(filename));
	if (read_ret > CHAMP_MAX_SIZE)
		return (ft_ret_err(MAX_PROG_SIZE_ERR));
	if ((unsigned int)read_ret != prog_size)
		return (ft_ret_err(PROG_SIZE_ERR));
	return (SUCCESS);
}

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
	if (handle_read_prog_err(read_ret, filename, player->header.prog_size)
		== FAILURE)
	{
		ft_strdel(&buff);
		return (FAILURE);
	}
	ft_memcpy(player->prog, buff, read_ret);
	ft_strdel(&buff);
	return (SUCCESS);
}
