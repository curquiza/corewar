#include "asm.h"

static t_ex_ret		name_check_before(char *line, int nb_line)
{
	char	*start;
	char	*start_line;

	if ((start = ft_strchr(line, '"')) == NULL)
		return (parse_error(nb_line, NO_NAME));
	
	start_line = line + ft_strlen(NAME_CMD_STRING);
	while (start_line != start)
	{
		if (is_whitespace(*start_line))
			start_line++;
		else
			return (parse_error_token(nb_line, start_line, INVALID_TOKEN));
	}
	return (SUCCESS);
}

static t_ex_ret		name_check_after(char *line, int nb_line)
{
	char	*start;
	char	*end;
	char	*start_line;

	start = ft_strchr(line, '"') + 1;
	
	if (count_char(start, '"') != 1)
		return (parse_error_token(nb_line, start, ERR_QUOTE));

	end = ft_strrchr(line, '"');
	
	start_line = end + 1;
	while (*start_line)
	{
		if (is_whitespace(*start_line))
			start_line++;
		else
			return (parse_error_token(nb_line, start_line, INVALID_TOKEN));
	}
	return (SUCCESS);
}

static int			get_name(t_src_file *file, char **line)
{
	char	*start;
	char	*end;
	int		size;

	if (name_check_before(*line, file->nb_line) == FAILURE)
		return (FAILURE);
	if (read_again(file, line) == FAILURE)
		return (FAILURE);
	if (name_check_after(*line, file->nb_line) == FAILURE)
		return (FAILURE);
	start = ft_strchr(*line, '"') + 1;
	end = ft_strrchr(*line, '"');
	size = end - start > PROG_NAME_LENGTH + 1 ? -1 : end - start;
	if (size == -1)
		return (parse_error(file->nb_line, BIG_NAME));
	ft_memcpy(file->header.prog_name, start, size);
	if (*(file->header.prog_name) == '\0')
		return (parse_error(file->nb_line, NO_NAME));
	return (SUCCESS);
}

t_ex_ret		return_parse_name(t_src_file *file, int ret)
{
	if (ret == -1)
		return (ft_ret_err(ERR_GNL));
	if (ret == 0 || *(file->header.prog_name) == '\0')
		return (parse_error(file->nb_line, NO_NAME));
	return (SUCCESS);
}

t_ex_ret		parse_name(t_src_file *file)
{
	char	*line;
	int		ret;

	while ((ret = get_trim_line(file->fd, &line)) == 1)
	{
		file->nb_line++;
		if (*line == '#' || *line == '\0')
		{
			ft_strdel(&line);
			continue ;
		}
		else if ((ft_strncmp(line, NAME_CMD_STRING,
			ft_strlen(NAME_CMD_STRING))) == 0)
		{
			ret = get_name(file, &line);
			ft_strdel(&line);
			return (ret);
		}
		else
			break ;
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (return_parse_name(file, ret));
}
