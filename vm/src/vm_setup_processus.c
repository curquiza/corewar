#include "vm.h"

t_processus	*new_processus(int index, t_vm *vm)
{
	t_processus		*new;

	if (!(new = ft_memalloc(sizeof(*new))))
		exit_malloc_err();
	new->pc = index;
	vm->total_proc += 1;
	return (new);
}

void	add_processus(t_processus **alst, t_processus *new)
{
	if (!alst)
		return ;
	else if (!*alst)
		*alst = new;
	else
	{
		new->next = *alst;
		*alst = new;
	}
}

/*static void	add_back_processus(t_processus **alst, t_processus *new, int num)*/
/*{*/
	/*t_processus	*tmp;*/

	/*if (alst == NULL)*/
		/*return ;*/
	/*new->reg[0] = num;*/
	/*tmp = *alst;*/
	/*if (*alst == NULL)*/
		/**alst = new;*/
	/*else*/
	/*{*/
		/*while (tmp->next)*/
			/*tmp = tmp->next;*/
		/*tmp->next = new;*/
	/*}*/
/*}*/

void	create_all_first_processus(t_vm *vm)
{
	int		i;
	int		index;

	i = 0;
	while (i < vm->total_players)
	{
		index = get_beginning_index(i, vm);
		/*if (flag_is_applied(ZAZ_FLAG, vm) == TRUE)*/
			/*add_back_processus(&vm->proc, new_processus(index, vm), ~vm->player[i].num);*/
		/*else*/
		/*{*/
			add_processus(&vm->proc, new_processus(index, vm));
			vm->proc->reg[0] = ~vm->player[i].num;
		/*}*/
		i++;
	}
}
