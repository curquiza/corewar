#include "vm.h"

t_ex_ret	open_file(char *filename)
{
	int		fd;
	char	*err_str;

	if ((fd = open(filename, O_RDONLY)) <= 0)
	{
		err_str = ft_strjoin("Open error: ", filename);
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
		fd_str = ft_itoa(fd);
		err_str = ft_strjoin("Close error: ", fd_str);
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

	err_str = ft_strjoin("Read error: ", filename);
	perror(err_str);
	ft_strdel(&err_str);
	return (FAILURE);
}
