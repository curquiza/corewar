#include "vm.h"

t_ex_ret	read_magic(char *filename, int fd, t_header *header)
{
	char	buff[4];
	int		read_ret;

	read_ret = read(fd, buff, 4);
	if (read_ret == -1)
		return (read_error(filename));
	if (read_ret != 4 || COREWAR_EXEC_MAGIC != str_to_uint32(buff))
	{
		ft_dprintf(2, HEADER_ERR);
		return (EXIT_FAILURE);
	}
	/*printf("real magic = %0x\n", COREWAR_EXEC_MAGIC); //DEBUG*/
	/*printf("my magic = %0x\n", str_to_uint32(buff));   //DEBUG*/
	header->magic = str_to_uint32(buff);
	return (EXIT_SUCCESS);
}

t_ex_ret	read_name(char *filename, int fd, t_header *header)
{
	char	buff[PROG_NAME_LENGTH];
	int		read_ret;

	read_ret = read(fd, buff, PROG_NAME_LENGTH);
	if (read_ret == -1)
		return (read_error(filename));
	if (read_ret != PROG_NAME_LENGTH)
	{
		ft_dprintf(2, HEADER_ERR);
		return (EXIT_FAILURE);
	}
	/*ft_bzero(header->prog_name, PROG_NAME_LENGTH + 1);*/
	ft_memcpy(header->prog_name, buff, PROG_NAME_LENGTH);
	return (EXIT_SUCCESS);
}

t_ex_ret	read_zero_block(char *filename, int fd)
{
	char	buff[4];
	int		read_ret;

	read_ret = read(fd, buff, 4);
	if (read_ret == -1)
		return (read_error(filename));
	if (read_ret != 4 || str_to_uint32(buff) != 0)
	{
		ft_dprintf(2, HEADER_ERR);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_ex_ret	read_prog_size(char *filename, int fd, t_header *header)
{
	char	buff[4];
	int		read_ret;

	read_ret = read(fd, buff, 4);
	if (read_ret == -1)
		return (read_error(filename));
	if (read_ret != 4)
	{
		ft_dprintf(2, HEADER_ERR);
		return (EXIT_FAILURE);
	}
	header->prog_size = str_to_uint32(buff);
	return (EXIT_SUCCESS);
}

t_ex_ret	read_comment(char *filename, int fd, t_header *header)
{
	char	buff[COMMENT_LENGTH];
	int		read_ret;

	read_ret = read(fd, buff, COMMENT_LENGTH);
	if (read_ret == -1)
		return (read_error(filename));
	if (read_ret != COMMENT_LENGTH)
	{
		ft_dprintf(2, HEADER_ERR);
		return (EXIT_FAILURE);
	}
	ft_bzero(header->comment, COMMENT_LENGTH + 1);
	ft_memcpy(header->comment, buff, COMMENT_LENGTH);
	return (EXIT_SUCCESS);
}
