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
# define NO_EXIST		"No such file or directory."
# define PERM_DENIED	"Permission denied."
# define ERR_READ	    "Read error."
# define NO_NAME		"Name was expected in the source file."
# define NO_COMMENT		"Comment was expected in the source file."
# define ERR_QUOTE		"Bad quoting."

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
t_ex_ret        parse(t_src_file *file, int fd);
t_ex_ret        parse_name(t_src_file *file, int fd);
t_ex_ret        parse_comment(t_src_file *file, int fd);
t_ex_ret     	parse_error(int line, char *message);

/*
** TOOLS
*/
int     get_trim_line(const int fd, char **line);
int     count_char(char *s, char c);

#endif
