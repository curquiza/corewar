/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_lst_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:43:56 by curquiza          #+#    #+#             */
/*   Updated: 2017/09/16 15:08:29 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_arg	*ft_new_arglst(t_arg **alst)
{
	t_arg	*tmp;

	if (alst == NULL)
		return (NULL);
	tmp = *alst;
	if (*alst == NULL)
	{
		*alst = ft_memalloc(sizeof(t_arg));
		return (*alst);
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_memalloc(sizeof(t_arg));
		return (tmp->next);
	}
}
