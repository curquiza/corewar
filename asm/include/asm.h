#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"
# include "struct.h"
# include "error.h"
# include "lexer.h"
# include "parser.h"
# include "encode.h"
# include <fcntl.h>
# include <sys/stat.h>

# define PROG_NAME      "asm: "
# define INPUT_EXT		".s"
# define OUTPUT_EXT		".cor"
# define OPTIONS		"a"
# define FLAG_A			1


/*
** GLOBAL VARIABLES
*/
extern int		g_flags;
extern t_op 	g_op_tab[NB_OPCODE + 1];
t_src_file		*g_file;

/*
** INIT
*/
int				get_options(int *argc, char ***argv);

/*
** INPUT
*/
t_ex_ret		read_file(t_src_file *file, t_list **head);
void			print_file(t_list *file);

/*
** OUTPUT
*/
t_ex_ret		write_output_file(t_src_file *file);
t_ex_ret		write_output_stdout(t_src_file *file);

/*
** ERROR
*/
t_ex_ret		put_error(char *e);
int				put_error_code(char *e, int code);
t_ex_ret     	parse_error(int line, char *message);
t_ex_ret     	parse_error_token(int line, char *token, char *message);

/*
** TOOLS
*/
void 			del(void *content, size_t content_size);
int     		get_trim_line(const int fd, char **line);
int     		count_char(char *s, char c);
t_ex_ret		list_to_array(t_list *input, char ***array, int len);

#endif
