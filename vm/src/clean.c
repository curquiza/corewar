/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 19:41:41 by curquiza          #+#    #+#             */
/*   Updated: 2019/01/09 19:41:46 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	clean_all(void)
{
	t_processus	*tmp;
	t_processus	*proc;

	proc = g_vm->proc;
	while (proc)
	{
		tmp = proc;
		proc = proc->next;
		free(tmp);
	}
}
