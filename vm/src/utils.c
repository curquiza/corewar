/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 10:51:51 by curquiza          #+#    #+#             */
/*   Updated: 2019/01/10 15:01:46 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		exit_malloc_err(void)
{
	clean_all();
	ft_dprintf(2, "Malloc error\n");
	exit(FAILURE);
}

t_bool		flag_is_applied(int flag, t_vm *vm)
{
	return ((flag & vm->flag) == flag);
}

t_player	*get_player(int num, t_player *players, int total_players)
{
	int		i;

	i = 0;
	while (i < total_players)
	{
		if (players[i].num == num)
			return (&players[i]);
		i++;
	}
	return (NULL);
}
