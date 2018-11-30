#include "asm.h"

static t_ex_ret		read_lines(t_src_file *file, int fd)
{
	char	*line;
	int		ret;

	while ((ret = get_trim_line(fd, &line)) == 1)
	{
		file->nb_line++;
		if (*line == '#' || *line == '\0')
		{
			ft_strdel(&line);
			continue ;
		}
		else
		{
			ft_putendl(line);
			ft_strdel(&line);
		}
	}
	if (ret == -1)
		return (ft_ret_err(ERR_GNL));
	return (ret);
}

t_ex_ret	parse_instr(t_src_file *file, int fd)
{
	int		ret;

	ret = read_lines(file, fd);
	return (SUCCESS);
}