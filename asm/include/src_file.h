#ifndef SRC_FILE_H
# define SRC_FILE_H

typedef struct					s_src_file
{
	int							fd;
	t_header					header;	
	char						*filename;
	int							nb_line;
}								t_src_file;

t_src_file		*g_file;

#endif

