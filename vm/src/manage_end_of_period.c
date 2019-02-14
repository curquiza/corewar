/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_end_of_period.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 10:50:09 by curquiza          #+#    #+#             */
/*   Updated: 2019/01/10 14:09:55 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	handle_no_enough_live(t_vm *vm)
{
	print_str("\tTotal lives are fewer than NBR_LINE : ", FEW, vm);
	print_compare_intvar(vm->lives, NBR_LIVE, FEW, vm);
	print_str("\tIncrementing verif : ", ALL, vm);
	print_upd_intvar(vm->verif, vm->verif + 1, ALL, vm);
	vm->verif += 1;
	if (vm->verif >= MAX_CHECKS)
	{
		print_str_int("\tNb of verif reaches the maximum", MAX_CHECKS, FEW, vm);
		print_str("\tDecrementing cycles_to_die : ", ALL, vm);
		print_upd_intvar(vm->cycles_to_die, vm->cycles_to_die - CYCLE_DELTA,
						ALL, vm);
		vm->cycles_to_die -= CYCLE_DELTA;
		print_str("\tReseting verif\n", ALL, vm);
		vm->verif = 0;
	}
}

static void	manage_cycles_verification(t_vm *vm)
{
	print_str("\tReseting current_cycles\n", ALL, vm);
	vm->current_cycles = 0;
	if (vm->lives < NBR_LIVE)
		handle_no_enough_live(vm);
	else
	{
		print_str("\tDecrementing cycles_to_die : ", FEW, vm);
		print_upd_intvar(vm->cycles_to_die, vm->cycles_to_die - CYCLE_DELTA,
						FEW, vm);
		vm->cycles_to_die -= CYCLE_DELTA;
		print_str("\tReseting verif\n", ALL, vm);
		vm->verif = 0;
	}
	print_str("\tReseting lives\n", ALL, vm);
	vm->lives = 0;
}

static void	supp_processus(t_processus **proc, t_vm *vm)
{
	t_processus	*supp;

	print_str("+", ALL, vm);
	supp = *proc;
	*proc = (*proc)->next;
	vm->memory[supp->pc].proc = FALSE;
	ft_bzero(supp, sizeof(*supp));
	free(supp);
	vm->total_proc -= 1;
}

static void	kill_or_reset_processus(t_processus **proc, t_vm *vm)
{
	t_processus	*current;

	if (!proc || !*proc)
		return ;
	current = *proc;
	while (current->next)
	{
		if (current->next->live == FALSE)
			supp_processus(&current->next, vm);
		else
		{
			current->next->live = FALSE;
			current = current->next;
		}
	}
	if (*proc)
	{
		if ((*proc)->live == FALSE)
			supp_processus(proc, vm);
		else
			(*proc)->live = FALSE;
	}
	print_str("\n", ALL, vm);
}

void		manage_end_of_period(t_vm *vm)
{
	print_str_int("Cycles to die reached", vm->cycles_to_die, FEW, vm);
	print_str("Reseting all processus lives\n", ALL, vm);
	print_str("and killing all dead processus : ", ALL, vm);
	kill_or_reset_processus(&vm->proc, vm);
	print_str("Managing cycles verifications\n", ALL, vm);
	manage_cycles_verification(vm);
	if (vm->proc == NULL)
	{
		print_str("No remaining processus. Gonna stop the game...\n", FEW, vm);
		vm->run = OFF;
	}
	else if (vm->cycles_to_die <= 0)
	{
		print_str("Cycles to die reaches 0. Gonna stop the game...\n", FEW, vm);
		vm->run = OFF;
	}
}
