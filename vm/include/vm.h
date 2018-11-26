#ifndef VM_H
# define VM_H

# include "libft.h"
# include "op.h"

# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <ncurses.h>

# define DEFINE_ERR			"Value not conformed in op.h file"
# define HEADER_ERR			"Wrong header format"
# define PROG_SIZE_ERR		"Prog size in header differs from the real prog size"
# define MAX_PROG_SIZE_ERR	"Prog size is too large"
# define MAX_PLAYER_ERR		"Too many champions"
# define PLAYER_NUM_ERR1	"2 arguments are needed for -n flag"
# define PLAYER_NUM_ERR2	"Player number must be a positive integer value"
# define DUMP_CYCLE_ERR1	"1 argument is needed for -dump flag"
# define DUMP_CYCLE_ERR2	"Dump cycle must be a positive integer value"
# define VISU_ERR			"Impossible to select 2 different types of visual"
# define WRONG_FLAG_ERR		"Not an available flag"
# define VISU_COLOR_ERR		"Terminal does not support color, impossible to launch visual"
# define VISU_SIZE_ERR		"Window too small to launch visual"

# define NUM_FLAG_STR		"-n"
# define ZAZ_FLAG_STR		"-zaz"
# define DUMP_FLAG_STR		"-dump"
# define VISU_FLAG_STR		"-visual"
# define MINI_VISU_FLAG_STR	"-mini-visual"

# define BYTES_PER_LINE_32	32
# define BYTES_PER_LINE_64	64

# define VISU_LINES			83
# define VISU_COLS			364
# define MINI_VISU_LINES	52
# define MINI_VISU_COLS		204

# define DUMP_FLAG			1 // (1 << 0)
# define VISU_FLAG			2 // (1 << 1)
# define MINI_VISU_FLAG		4 // (1 << 2)
# define ZAZ_FLAG			8 // (1 << 3)

typedef enum	e_visu_type
{
	DEF_V,
	MINI_V
}				t_visu_type;

typedef enum	e_color_pair
{
	DEF_PAIR,
	CYAN_PAIR,
	PINK_PAIR,
	GREEN_PAIR,
	YELLOW_PAIR
}				t_color_pair;

typedef struct	s_memcase
{
	t_byte			value;
	char			color[20];
	t_color_pair	color_visu;
}				t_memcase;

typedef struct	s_player
{
	t_header	header;
	int			num;
	t_byte		prog[CHAMP_MAX_SIZE];
}				t_player;

typedef struct	s_processus
{
	int					index;
	int					cycles;
	t_byte				opcode;
	t_bool				live;
	int					reg[REG_NUMBER];
	unsigned short		pc;
	struct s_processus	*next;
}				t_processus;

typedef struct	s_visu
{
	t_bool	enabled;
	int		type;
}		t_visu;

typedef struct 	s_vm
{
	t_memcase	memory[MEM_SIZE];
	t_player	player[MAX_PLAYERS];
	int			players_number;
	int			flag;
	int			dump_cycle;
	t_processus	*proc;
	int			total_cycles;
	int			current_cycles;
	int			cycles_to_die;
	int			lives;
	int			verif;
	int			last_live_player_id;
	t_visu		visu;
	// tableau de pointeur sur fonction des 16 instructions -> instruction[17]
}				t_vm;

t_vm	*g_vm;

/*
** === FUNCTIONS ===============================================================
*/

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
** Dump flag
*/
void			dump_memory(t_vm *vm);

/*
** Clean
*/
void			clean_all(void);

/*
** Visual
*/
void	start_visu(t_vm *vm);

/*
** Misc
*/
t_ex_ret		usage_ret_err(void);
void			exit_malloc_err(void);
t_bool			flag_is_applied(int flag, t_vm *vm);

#endif
