/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_syscall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 10:49:56 by curquiza          #+#    #+#             */
/*   Updated: 2019/01/10 10:49:57 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_ex_ret	open_file(char *filename, int args, int perm)
{
	int		fd;
	char	*err_str;

	if ((fd = open(filename, args, perm)) <= 0)
	{
		if (!(err_str = ft_strjoin("Open error: ", filename)))
			exit_malloc_err();
		perror(err_str);
		ft_strdel(&err_str);
		return (FAILURE);
	}
	return (fd);
}

t_ex_ret	close_fd(int fd)
{
	char	*fd_str;
	char	*err_str;

	if (close(fd) == -1)
	{
		if (!(fd_str = ft_itoa(fd)))
			exit_malloc_err();
		if (!(err_str = ft_strjoin("Close error: ", fd_str)))
		{
			ft_strdel(&fd_str);
			exit_malloc_err();
		}
		perror(err_str);
		ft_strdel(&fd_str);
		ft_strdel(&err_str);
		return (FAILURE);
	}
	return (SUCCESS);
}

t_ex_ret	read_error(char *filename)
{
	char	*err_str;

	if (!(err_str = ft_strjoin("Read error: ", filename)))
		exit_malloc_err();
	perror(err_str);
	ft_strdel(&err_str);
	return (FAILURE);
}
