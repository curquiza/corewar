#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"
# include <fcntl.h>
# include <sys/stat.h>

# define PROG_NAME      "asm: "
# define INPUT_EXT		".s"
# define OUTPUT_EXT		".cor"
# define OPTIONS		"a"
# define USAGE_OPTS 	"-a : Instead of creating a .cor file, outputs a stripped and annotated version of the code to the standard output"
# define USAGE			"usage: ./asm [-"OPTIONS"] <sourcefile.s>\n\t" USAGE_OPTS
# define ILLEGAL_OPTION	PROG_NAME "illegal option\n" USAGE
# define FLAG_A			1
# define NEWLINE		"\n"
/*
** ERRORS
*/
# define ERR_MALLOC		"Malloc error."
# define ERR_OPEN		"Open error."
# define NO_EXIST		"No such file or directory."
# define PERM_DENIED	"Permission denied."
# define ERR_GNL	    "Read line error."
# define NO_NAME		"Name was expected in the source file."
# define BIG_NAME		"Name is too long."
# define NO_COMMENT		"Comment was expected in the source file."
# define BIG_COMMENT	"Comment is too long."
# define ERR_QUOTE		"Bad quoting."

typedef struct	s_token
{
	struct s_token		*prev;
	struct s_token		*next;
	char				*str;
	unsigned short		offset; 	// memory size is a short
	unsigned char		encode[4]; 	// from 1 to 4 bytes
	unsigned char		size; 		// from 1 to 4 bytes
	t_arg_type			arg_type; 	// T_REG: 1 // T_DIR: 2 // T_IND: 4 // T_LAB: 8 //

}				t_token;

typedef struct	s_src_file
{
	t_header	header;	
	char		*filename;
	t_token		*tokens;
	t_token		*current;
	int			nb_line;
	int			nb_col;

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
t_ex_ret        parse_instr(t_src_file *file, int fd);
t_ex_ret		check_syntax(int line, t_token *current, t_token *new);

/*
** TOKENS
*/
t_ex_ret		link_token(t_src_file *file, char *line, int len);
t_ex_ret		create_token(t_token **elem, char *line, int len);
void			add_token(t_token **tokens, t_token *new);
void			remove_current_token(t_src_file *file);
void			print_tokens(t_token *tokens);
void			print_rev_tokens(t_token *tokens);
void			free_tokens(t_token **tokens);

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
