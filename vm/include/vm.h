#ifndef VM_H
# define VM_H

# include "libft.h"
# include "op.h"

# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <ncurses.h>

/*
** === DEFINE ==================================================================
*/

/*
** Error messages
*/
# define DEFINE_ERR			"Value not conformed in op.h file"
# define HEADER_ERR			"Wrong header format"
# define PROG_SIZE_ERR		"Prog size in header differs from the real prog size"
# define MAX_PROG_SIZE_ERR	"Prog size is too large"
# define MAX_PLAYER_ERR		"Too many champions"
# define PLAYER_NUM_ERR1	"2 arguments are needed for -n flag"
# define PLAYER_NUM_ERR2	"Player number must be a positive integer value"
# define DUMP_CYCLE_ERR1	"1 argument is needed for -dump flag"
# define DUMP_CYCLE_ERR2	"Dump cycle must be a positive integer value"
# define VERBOSE_ERR1		"1 argument is needed for -verbose flag"
# define VERBOSE_ERR2		"Not a valid argument for -verbose flag (1 or 2 accepted)"
# define WRONG_FLAG_ERR		"Not an available flag"
# define VISU_COLOR_ERR		"Terminal does not support color, impossible to launch visual"
# define VISU_SIZE_ERR		"Window too small to launch visual"
# define VISU_TRACE_ERR		"Error when opening trace file, impossible to launch visual"

/*
** Flags
*/
# define NUM_FLAG_STR		"-n"
# define ZAZ_FLAG_STR		"-zaz"
# define DUMP_FLAG_STR		"-dump"
# define VISU_FLAG_STR		"-visual"
# define VERBOSE_FLAG_STR	"-verbose"

/*
** Visu
*/
# define VISU_LINES			83
# define VISU_COLS			364
# define MINI_VISU_LINES	52
# define MINI_VISU_COLS		204

# define MEM_WIN_X			206
# define MEM_WIN_Y			66
# define MINI_MEM_WIN_X		110
# define MINI_MEM_WIN_Y		50
# define CYCLES_WIN_X		25
# define CYCLES_WIN_Y		12
# define LIVES_WIN_X		25
# define LIVES_WIN_Y		12
# define PROC_WIN_X			25
# define PROC_WIN_Y			27
# define PLAYER_WIN_X		25
# define PLAYER_WIN_Y		6
# define USAGE_WIN_X		30
# define USAGE_WIN_Y		8

# define MINI_VISU_MEM_PART	48

# define TRACE_FILE			"trace.txt"

/*
** Misc
*/
# define BYTES_PER_LINE_32	32
# define BYTES_PER_LINE_64	64
# define OP_NUMBER			16
# define OCP_MASQ			3
# define NUM_REG_SIZE		1

/*
** === STRUCT AND ENUM =========================================================
*/

/*
** FLAGS
*/

enum			s_flag
{
	DUMP_FLAG = 1,
	VISU_FLAG = 2,
	VERBOSE_FLAG = 4,
	ZAZ_FLAG = 8
};

typedef enum	s_verbose
{
	NONE,
	FEW,
	ALL,
}				t_verbose;

/*
** VISU ***
*/
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

typedef struct	s_visu
{
	t_bool	enabled;
	int		type;
	t_bool	pause;
	t_bool	next_step;
	WINDOW	*mem_win;
	WINDOW	*cycles_win;
	WINDOW	*lives_win;
	WINDOW	*proc_win;
	WINDOW	*players_win[MAX_PLAYERS];
	WINDOW	*usage_win;
	int		mem_part;
	int		proc_id;
}				t_visu;

/*
** VM ***
*/

typedef enum	s_run
{
	ON,
	OFF,
	BREAK
}				t_run;

typedef struct	s_processus
{
	unsigned short		pc;
	int					cycles;
	struct s_op			*current_op;
	t_bool				live;
	int					reg[REG_NUMBER];
	int					carry;
	struct s_processus	*next;
}				t_processus;

typedef struct	s_memcase
{
	t_byte			value;
	char			color[20];
	t_color_pair	color_visu;
	t_bool			proc;
}				t_memcase;

typedef struct	s_player
{
	t_header	header;
	int			num;
	t_byte		prog[CHAMP_MAX_SIZE];
}				t_player;

typedef struct 	s_vm
{
	t_run			run;
	t_memcase		memory[MEM_SIZE];
	t_player		player[MAX_PLAYERS];
	int				total_players;
	int				flag;
	int				dump_cycle;
	t_processus		*proc;
	int				total_proc;
	int				total_cycles;
	int				current_cycles;
	int				cycles_to_die;
	int				lives;
	int				verif;
	int				last_live_player;
	t_visu			visu;
	t_verbose		verbose;
	int				trace_fd;
}				t_vm;

/*
** OPERATION ***
*/

typedef struct	s_param
{
	t_byte		type;
	int			size;
	int			value;
}				t_param;

typedef struct	s_op
{
	t_byte		opcode;
	char		*name;
	int			param_nb;
	t_byte		param_type[MAX_ARGS_NUMBER];
	int			cycles;
	t_bool		ocp;
	t_bool		index;
	void		(*func)(t_vm *, t_processus *, t_param *);
}				t_op;

/*
** === GLOBALS =================================================================
*/

t_op	g_op[OP_NUMBER];
t_vm	*g_vm;

/*
** === FUNCTIONS ===============================================================
*/

/*
** Files manager
*/
t_ex_ret		open_file(char *filename, int args, int perm);
t_ex_ret		close_fd(int fd);
t_ex_ret		read_error(char *filename);

/*
** Conversions
*/
uint32_t		str_to_uint32(char *str);
uint32_t		memvalue_to_uint32(t_memcase *vm_mem, unsigned short index,
									int size);

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
t_processus		*new_processus(int index, t_vm *vm);
void			add_processus(t_processus **alst, t_processus *new);
void			create_all_first_processus(t_vm *vm);
int				get_beginning_index(int num, t_vm *vm);
void			vm_setup(t_vm *vm);

/*
** Dump flag
*/
void			dump_memory(t_vm *vm);

/*
** Verbose flag
*/
void			print_str(char *s, t_verbose type, t_vm *vm);
void			print_str2(char *s1, char *s2, t_verbose type, t_vm *vm);
void			print_str_int(char *s, int n, t_verbose type, t_vm *vm);
void			print_upd_intvar(int v1, int v2, t_verbose type, t_vm *vm);
void			print_compare_intvar(int v1, int v2, t_verbose type, t_vm *vm);

/*
** Game
*/
void			manage_end_of_period(t_vm *vm);
void			exec_all_proc(t_vm *vm);

/*
** Operations
*/
t_bool			parse_op_params(t_vm *vm, t_processus *proc, t_param *params);
void			op_live(t_vm *vm, t_processus *proc, t_param *params);
void			op_ld(t_vm *vm, t_processus *proc, t_param *params);
void			op_st(t_vm *vm, t_processus *proc, t_param *params);
void			op_and(t_vm *vm, t_processus *proc, t_param *params);
void			op_or(t_vm *vm, t_processus *proc, t_param *params);
void			op_xor(t_vm *vm, t_processus *proc, t_param *params);
void			op_zjmp(t_vm *vm, t_processus *proc, t_param *params);
void			op_ldi(t_vm *vm, t_processus *proc, t_param *params);
void			op_sti(t_vm *vm, t_processus *proc, t_param *params);
void			op_fork(t_vm *vm, t_processus *proc, t_param *params);

/*
** Clean
*/
void			clean_all(void);

/*
** Visual
*/
void			start_visu(t_vm *vm);
void			display_visu(t_vm *vm);
void			create_visu_subwin(t_vm *vm);
void			create_mini_visu_subwin(t_vm *vm);
void			getkey(t_vm *vm);

/*
** Misc
*/
t_ex_ret		usage_ret_err(void);
void			exit_malloc_err(void);
t_bool			flag_is_applied(int flag, t_vm *vm);
int				get_mem_index(unsigned short index);
t_bool			is_valid_reg_index(int index);
int				get_value_according_to_type(t_vm *vm, t_processus *proc,
											t_param *p);
void			store_4bytes(t_vm *vm, unsigned short index, int value,
							t_processus *proc);

#endif
