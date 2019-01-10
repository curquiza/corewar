/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 10:51:56 by curquiza          #+#    #+#             */
/*   Updated: 2019/01/10 10:51:57 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_str(char *s, t_verbose type, t_vm *vm)
{
	if ((vm->verbose == NONE && type != NONE)
		|| (vm->verbose == FEW && type > FEW))
		return ;
	ft_dprintf(vm->trace_fd, "%s", s);
}

void	print_str2(char *s1, char *s2, t_verbose type, t_vm *vm)
{
	if ((vm->verbose == NONE && type != NONE)
		|| (vm->verbose == FEW && type > FEW))
		return ;
	ft_dprintf(vm->trace_fd, "%s %s\n", s1, s2);
}

void	print_str_int(char *s, int n, t_verbose type, t_vm *vm)
{
	if ((vm->verbose == NONE && type != NONE)
		|| (vm->verbose == FEW && type > FEW))
		return ;
	ft_dprintf(vm->trace_fd, "%s (%d)\n", s, n);
}

void	print_upd_intvar(int v1, int v2, t_verbose type, t_vm *vm)
{
	if ((vm->verbose == NONE && type != NONE)
		|| (vm->verbose == FEW && type > FEW))
		return ;
	ft_dprintf(vm->trace_fd, "%d -> %d\n", v1, v2);
}

void	print_compare_intvar(int v1, int v2, t_verbose type, t_vm *vm)
{
	if ((vm->verbose == NONE && type != NONE)
		|| (vm->verbose == FEW && type > FEW))
		return ;
	ft_dprintf(vm->trace_fd, "%d // %d\n", v1, v2);
}
