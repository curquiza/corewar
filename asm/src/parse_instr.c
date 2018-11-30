#include "asm.h"

static t_ex_ret		tokenize(char *line)
{
	char	**tokens;

	tokens = ft_strsplit(line, ' ');
	ft_puttab(tokens);
	return (SUCCESS);
}


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
			ft_printf("-- line: %s\n", line);
			if ((ret = tokenize(line)) == FAILURE)
				break ;
			ft_strdel(&line);
		}
	}
	line ? ft_strdel(&line) : 0;
	if (ret == -1)
		return (ft_ret_err(ERR_GNL));
	return (ret);
}

t_ex_ret	parse_instr(t_src_file *file, int fd)
{
	int		ret;

	ret = read_lines(file, fd);
	return (ret);
}