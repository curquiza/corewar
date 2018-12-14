#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"
# include "error.h"
# include "lexer.h"
# include "parser.h"
# include <fcntl.h>
# include <sys/stat.h>

# define PROG_NAME      "asm: "
# define INPUT_EXT		".s"
# define OUTPUT_EXT		".cor"
# define OPTIONS		"a"
# define FLAG_A			1

extern int		g_flags;
t_src_file		*g_file;

/*
** INIT
*/
int				get_options(int *argc, char ***argv);

/*
** OUTPUT
*/
t_ex_ret		write_output_file(t_src_file *file);
t_ex_ret		write_output_stdout(t_src_file *file);

/*
** TOOLS
*/
t_ex_ret		put_error(char *e);
int				put_error_code(char *e, int code);
int     		get_trim_line(const int fd, char **line);
int     		count_char(char *s, char c);

#endif
