#ifndef VM_H
# define VM_H

# include "libft.h"
# include "op.h"

# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>

# define DEFINE_ERR			"Value not conformed in op.h file"
# define HEADER_ERR			"Wrong header format"
# define PROG_SIZE_ERR		"Prog size in header differs from the real prog size"
# define MAX_PROG_SIZE_ERR	"Prog size is too large"
# define MAX_PLAYER_ERR		"Too many champions"
# define PLAYER_NUM_ERR		"Player number must be a positive integer value"
# define DUMP_CYCLE_ERR		"Dump cycle must be a positive integer value"
# define WRONG_FLAG_ERR		"Not an available flag"

# define NUM_FLAG_STR	"-n"
# define ZAZ_FLAG_STR	"-zaz"
# define DUMP_FLAG_STR	"-dump"

# define DUMP_FLAG	(1 << 0) // 1
# define ZAZ_FLAG	(1 << 1) // 2

typedef struct	s_memcase
{
	char		value;
	char		*color;
}				t_memcase;

typedef struct	s_player
{
	t_header	header;
	int			num;
	char		*prog;
}				t_player;

typedef struct 	s_vm
{
	t_memcase	memory[MEM_SIZE];
	t_player	player[MAX_PLAYERS];
	int			players_number;
	int			flag;
	int			dump_cycle;
}				t_vm;

t_vm	*g_vm;

/*
** === FUNCTIONS ===============================================================
*/

void			print_usage(void);
void			exit_malloc_err(void);

/*
** Files manager
*/
t_ex_ret		open_file(char *filename);
t_ex_ret		close_fd(int fd);
t_ex_ret		read_error(char *filename);

/*
** Conversions
*/
uint32_t		str_to_uint32(char *str);

/*
** Parsing
*/
t_ex_ret		read_magic(char *filename, int fd, t_header *header);
t_ex_ret		read_name(char *filename, int fd, t_header *header);
t_ex_ret		read_zero_block(char *filename, int fd);
t_ex_ret		read_prog_size(char *filename, int fd, t_header *header);
t_ex_ret		read_comment(char *filename, int fd, t_header *header);
t_ex_ret		read_prog(char *filename, int fd, t_player *player);
t_ex_ret		manage_player(char *filename, t_vm *vm, int num);
t_ex_ret		manage_flag(char **argv, int *i, t_vm *vm);
t_ex_ret		parsing(int argc, char **argv, t_vm *vm);

/*
** Setup : before starting
*/
void			vm_setup(t_vm *vm);


/*
** Clean
*/
void			clean_all(void);

#endif
