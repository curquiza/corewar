#include "vm.h"

static void	load_proc_display(t_vm *vm)
{
	t_processus *proc;

	proc = vm->proc;
	while (proc)
	{
		vm->memory[proc->pc].proc = TRUE;
		proc = proc->next;
	}
}

static void	rm_proc_display(t_vm *vm)
{
	t_processus *proc;

	proc = vm->proc;
	while (proc)
	{
		vm->memory[proc->pc].proc = FALSE;
		proc = proc->next;
	}
}

static void		refresh_all(t_vm *vm)
{
	int		i;

	wrefresh(vm->visu.mem_win);
	wrefresh(vm->visu.cycles_win);
	wrefresh(vm->visu.lives_win);
	wrefresh(vm->visu.proc_win);
	wrefresh(vm->visu.usage_win);
	i = 0;
	while (i < vm->total_players)
	{
		wrefresh(vm->visu.players_win[i]);
		i++;
	}
}

void	display_visu(t_vm *vm)
{

	erase();
	load_proc_display(vm);
	if (vm->visu.type == MINI_V)
		dump_memory_mini_visu_part(vm, vm->visu.mem_win, vm->visu.mem_part);
	else
		dump_memory_visu(vm, vm->visu.mem_win);
	rm_proc_display(vm);
	display_cycles(vm, vm->visu.cycles_win);
	display_lives(vm, vm->visu.lives_win);
	if (vm->visu.proc_id > vm->total_proc)
		vm->visu.proc_id = vm->total_proc;
	display_proc(vm, vm->visu.proc_id, vm->visu.proc_win);
	display_players(vm, vm->visu.players_win);
	display_usage(vm, vm->visu.usage_win);
	refresh_all(vm);
}
