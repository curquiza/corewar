#include "asm.h"

t_ex_ret	write_output_file(t_src_file *file)
{
	int		fd;
	char	*tmp;
	char	*output;

	if (!(tmp = ft_strsub(file->filename, 0, ft_strrchr(file->filename, '.') - file->filename)))
		return (ft_ret_err(ERR_MALLOC));
	if (!(output = ft_strjoin(tmp, OUTPUT_EXT)))
		return (ft_ret_err(ERR_MALLOC));
	if ((fd = open(output, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		return (ft_ret_err(ERR_OPEN));
	write(fd, (const char*)&(file->header), sizeof(file->header));
	close(fd);
	return (SUCCESS);
}
