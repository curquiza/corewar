#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"
# include <fcntl.h>
# include <sys/stat.h>

# define PROG_NAME      "asm: "
# define OPTIONS		"a"
# define USAGE_OPTS 	"-a : Instead of creating a .cor file, outputs a stripped and annotated version of the code to the standard output"
# define USAGE			"usage: ./asm [-"OPTIONS"] <sourcefile.s>\n\t" USAGE_OPTS
# define ILLEGAL_OPTION	PROG_NAME "illegal option\n" USAGE
# define ERR_OPEN		": No such file or directory."
# define ERR_PERM	    ": Permission denied."
# define ERR_READ	    ": read error."

enum 		e_error
{
	NO_EXIST = -10,
	PERM_DENIED,
	READ_ERROR
};

typedef struct	s_src_file
{
	t_header	header;
}				t_src_file;

extern int		g_flags;
t_src_file		*g_file;

/*
** INIT & PARSING
*/
int				get_options(int *argc, char ***argv);
int				parse(t_src_file *file, int fd);

#endif
