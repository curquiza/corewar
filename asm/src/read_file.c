#include "asm.h"

/*
** read a file and store each line in an array of string.
*/

void			print_file(t_list *file)
{
	t_list	*tmp;

	tmp = file;
	while (tmp)
	{
		ft_printf("%s\n", (char*)tmp->content);
		tmp = tmp->next;
	}
}

t_ex_ret		read_file(t_src_file *file, t_list **head)
{
	int				ret;
	t_list			*elem;
	char			*line;

	while ((ret = get_next_line(file->fd, &line)) > 0)
	{
		if (!(elem = ft_lstnew(line, ft_strlen(line) + 1)))
			return (ft_ret_err(ERR_MALLOC));
		ft_lstadd_back(head, elem);
		ft_strdel(&line);
	}
	close(file->fd);
	if (ret == -1)
		return (ft_ret_err(ERR_GNL));
	return (SUCCESS);
}

t_ex_ret		read_again(t_src_file *file, char **line)
{
	char	*tmp_line;
	char	*tmp_read;

	tmp_read = NULL;
	while (count_char(*line, '"') < 2)
	{
		if ((get_next_line(file->fd, &tmp_read)) != 1)
			return (ft_ret_err(ERR_GNL));
		if (!(tmp_line = ft_strjoin3(*line, "\n", tmp_read)))
			return (put_error_code(ERR_MALLOC, -1));
		tmp_read ? free(tmp_read) : 0;
		*line ? free(*line) : 0;
		*line = tmp_line;
	}
	return (SUCCESS);
}
