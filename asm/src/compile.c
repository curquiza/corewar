/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 10:43:33 by sfranc            #+#    #+#             */
/*   Updated: 2019/02/14 13:41:12 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** After having parsed the file, get the size of the file.
*/

static void			fill_prog_size(t_src_file *file)
{
	int i;

	i = 0;
	while (file->ast[i])
		i++;
	if (file->ast[i - 1])
		file->header.prog_size =
			ft_swap_int(file->ast[i - 1]->offset + file->ast[i - 1]->size);
	else
		file->header.prog_size = 0;
}

/*
** COMPILE: Parse, encode and output.
** Everything happens here...
*/

t_ex_ret			compile(t_src_file *file)
{
	if ((parse_name(file)) == FAILURE)
		return (FAILURE);
	if ((parse_comment(file)) == FAILURE)
		return (FAILURE);
	if ((parser(file)) == FAILURE)
		return (FAILURE);
	fill_prog_size(file);
	if (ft_swap_int(file->header.prog_size) > CHAMP_MAX_SIZE)
		return (parse_error(0, CHAMP_TOO_LONG));
	if ((encode(file)) != SUCCESS)
		return (FAILURE);
	if (!(g_flags & FLAG_A))
	{
		if ((write_output_file(file)) == FAILURE)
			return (FAILURE);
	}
	else
		write_output_stdout(file);
	close(file->fd);
	return (SUCCESS);
}
