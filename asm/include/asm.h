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

enum 		e_error {
	NO_EXIST = -10,
	PERM_DENIED,
};

extern int	g_flags;

/*
** INIT
*/
int				get_options(int *argc, char ***argv);

#endif
