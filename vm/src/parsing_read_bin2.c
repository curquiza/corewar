/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_read_bin2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 10:51:45 by curquiza          #+#    #+#             */
/*   Updated: 2019/01/10 10:51:46 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_ex_ret	read_magic(char *filename, int fd, t_header *header)
{
	char	buff[4];
	int		read_ret;

	read_ret = read(fd, buff, 4);
	if (read_ret == -1)
		return (read_error(filename));
	if (read_ret != 4 || COREWAR_EXEC_MAGIC != str_to_uint32(buff))
		return (ft_ret_err(HEADER_ERR));
	header->magic = str_to_uint32(buff);
	return (SUCCESS);
}

t_ex_ret	read_name(char *filename, int fd, t_header *header)
{
	char	buff[PROG_NAME_LENGTH];
	int		read_ret;

	read_ret = read(fd, buff, PROG_NAME_LENGTH);
	if (read_ret == -1)
		return (read_error(filename));
	if (read_ret != PROG_NAME_LENGTH)
		return (ft_ret_err(HEADER_ERR));
	ft_memcpy(header->prog_name, buff, PROG_NAME_LENGTH);
	return (SUCCESS);
}

t_ex_ret	read_zero_block(char *filename, int fd)
{
	char	buff[4];
	int		read_ret;

	read_ret = read(fd, buff, 4);
	if (read_ret == -1)
		return (read_error(filename));
	if (read_ret != 4 || str_to_uint32(buff) != 0)
		return (ft_ret_err(HEADER_ERR));
	return (SUCCESS);
}

t_ex_ret	read_prog_size(char *filename, int fd, t_header *header)
{
	char	buff[4];
	int		read_ret;

	read_ret = read(fd, buff, 4);
	if (read_ret == -1)
		return (read_error(filename));
	if (read_ret != 4)
		return (ft_ret_err(HEADER_ERR));
	header->prog_size = str_to_uint32(buff);
	return (SUCCESS);
}

t_ex_ret	read_comment(char *filename, int fd, t_header *header)
{
	char	buff[COMMENT_LENGTH];
	int		read_ret;

	read_ret = read(fd, buff, COMMENT_LENGTH);
	if (read_ret == -1)
		return (read_error(filename));
	if (read_ret != COMMENT_LENGTH)
		return (ft_ret_err(HEADER_ERR));
	ft_bzero(header->comment, COMMENT_LENGTH + 1);
	ft_memcpy(header->comment, buff, COMMENT_LENGTH);
	return (SUCCESS);
}
