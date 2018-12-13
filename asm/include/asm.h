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
** INIT & PARSING
*/
int				get_options(int *argc, char ***argv);
t_ex_ret        parse(t_src_file *file);
t_ex_ret        parse_name(t_src_file *file);
t_ex_ret        parse_comment(t_src_file *file);
// t_ex_ret        parse_instr(t_src_file *file, int fd);
t_ex_ret		check_syntax(int line, t_token *current, t_token *new);

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
t_ex_ret     	parse_error(int line, char *message);
int     		get_trim_line(const int fd, char **line);
int     		count_char(char *s, char c);

#endif
