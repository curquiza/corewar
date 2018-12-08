#include "asm.h"

// SUCCESS -> un token est créé, FAILURE -> pas de token créé (EOF ou MALLOC ERR)
static t_bool				is_separator(char c)
{
	if (c == '\0' \
		|| c == ' ' \
		|| c == '\t' \
		|| c == '\n' \
		|| c == SEPARATOR_CHAR \
		|| c == LABEL_CHAR)
		return (TRUE);
	return (FALSE);
}				
static t_ex_ret 			get_next_token(t_src_file *file, char *line)
{
	t_ex_ret			ret;	
	char				*start;
	char				*tmp;
	int					len;

	ret = SUCCESS;
	start = line + file->nb_col;
	tmp = start;
	len = 0;
	while (42)
	{
		len++;
		ft_printf("char: %c-\n", *tmp);
		if (*tmp == DIRECT_CHAR)
		{
			ret = link_token(file, start, len);
			tmp++;
			break ;
		}
		else if ((is_separator(*tmp)))
		{
			ret = link_token(file, start, --len);
			break ;
		}
		else
			tmp++;

	}
	if (!*tmp)
		return (FAILURE);
	while ((is_separator(*tmp)))
		tmp++;
	file->nb_col += tmp - (line + file->nb_col);
	ft_printf("rest %s\n", line + file->nb_col);	
	return (ret);
}

static t_ex_ret			parse_line(t_src_file *file, char *line)
{
	const char	*sep = "<newline>";
	t_ex_ret	ret;

	file->nb_col = 0;
	while ((get_next_token(file, line)) == SUCCESS)
	{
		ft_printf("adding: %s\n", file->current->str);
		// print_tokens(file->tokens);
	}
	ft_printf("adding: %s\n", file->current->str);
	ret = link_token(file, (char*)sep, ft_strlen(sep));
	return (ret);
}

static t_ex_ret		read_lines(t_src_file *file, int fd)
{
	char		*line;
	t_ex_ret	ret;
	int			ret_gnl;

	while ((ret_gnl = get_trim_line(fd, &line)) == 1)
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
	if (ret_gnl == -1)
		return (ft_ret_err(ERR_GNL));
	return (ret);
}

t_ex_ret	parse_instr(t_src_file *file, int fd)
{
	t_ex_ret	ret;

	ret = read_lines(file, fd);
	print_tokens(file->tokens);
	return (ret);
}