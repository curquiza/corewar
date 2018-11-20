#ifndef VM_H
# define VM_H

# include "libft.h"
# include "op.h"

# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>

typedef		uint32_t t_exit;
typedef		unsigned char t_byte;

# define DEFINE_ERR		"Error: value not conformed in op.h file\n"
# define HEADER_ERR		"Error: wrong header format\n"
# define PROG_SIZE_ERR	"Error: prog size in header differs from the real prog size\n"
# define MAX_PLAYER_ERR	"Error: too many champions\n"
# define PLAYER_NUM_ERR	"Error: player number must be an integer value\n"
# define DUMP_CYCLE_ERR	"Error: dump cycle must be a positive integer value\n"
# define WRONG_FLAG_ERR	"Not an available flag\n"

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

/*
** Files manager
*/
t_exit			open_file(char *filename);
t_exit			close_fd(int fd);
t_exit			read_error(char *filename);

/*
** Conversions
*/
uint32_t		str_to_uint32(char *str);

/*
** Parsing
*/
t_exit			wrong_flag_err(char *s);
t_exit			player_num_err(void);
t_exit			dump_cycle_err(void);
t_exit			max_player_err(void);

t_exit			read_magic(char *filename, int fd, t_header *header);
t_exit			read_name(char *filename, int fd, t_header *header);
t_exit			read_zero_block(char *filename, int fd);
t_exit			read_prog_size(char *filename, int fd, t_header *header);
t_exit			read_comment(char *filename, int fd, t_header *header);
t_exit			read_prog(char *filename, int fd, t_player *player);

t_exit			manage_player(char *filename, t_vm *vm, int num);

t_exit			manage_flag(char **argv, int *i, t_vm *vm);

t_exit			parsing(int argc, char **argv, t_vm *vm);

/*
** Clean
*/
void			clean_all(void);

#endif
