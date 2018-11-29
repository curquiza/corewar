#include "asm.h"

t_ex_ret			read_file(t_src_file *file, int fd, char **input)
{
	char	*line;
	char	*tmp;
	int		ret;

	while ((ret = get_trim_line(fd, &line)) == 1)
	{
		ft_putendl(line);
		file->nb_line++;
		if (*line == '#' || *line == '\0')
		{
			ft_strdel(&line);
			continue ;
		}
		else
		{
			tmp = *input;
			if (!(*input = ft_strjoin(*input, line)))
				return (ft_ret_err(ERR_MALLOC));
			ft_strdel(&tmp);
		}
		ft_strdel(&line);
	}
	if (ret == -1)
		return (ft_ret_err(ERR_GNL));
	return (ret);
}

t_ex_ret	parse_instr(t_src_file *file, int fd)
{
	char	*input;
	int		ret;

    ret = read_file(file, fd, &input);
    ft_printf("INPUT %s\n", input);
    return (SUCCESS);
}