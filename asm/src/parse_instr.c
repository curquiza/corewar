#include "asm.h"

static int				is_label(char *line)
{
	const char	*label_chars = LABEL_CHARS;
	int			len;

	len = 0;
	while(*line && ft_strchr(label_chars, *line))
	{
		line++;
		len++;
	}
	if (len && *line == LABEL_CHAR)
		return (len);
	return (-1);
}

static t_ex_ret		parse_line(t_src_file *file, char *line)
{
	int			len;
	int			ret;
	t_token		*token;

	ret = SUCCESS;
	token = NULL;
	if ((len = is_label(line)) != -1)
	{
		ft_printf("add label");
		if ((ret = create_token(&token, line, len, T_LAB)) == SUCCESS)
			add_token(&(file->tokens), token);
		return (ret);
	}
	else
	{
		;//instruction
	}
	return (ret);
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
			if ((ret = parse_line(file, line)) == FAILURE)
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
	print_tokens(file->tokens);
	return (ret);
}