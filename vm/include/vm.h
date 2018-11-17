#ifndef VM_H
# define VM_H

# include "libft.h"
# include "op.h"

# include <fcntl.h>
# include <stdio.h>

typedef		uint32_t t_exit;
typedef		unsigned char t_byte;

# define DEFINE_ERR "Error: value not conformed in op.h file\n"
# define HEADER_ERR "Error: wrong header format\n"
# define PROG_SIZE_ERR "Error: prog size in header differs from the real prog size\n"

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
t_exit			parse_player(char *filename, t_player *player, int num);

/*
** Clean
*/
void			clean_all(void);

#endif
