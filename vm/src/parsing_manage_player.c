#include "vm.h"

static t_ex_ret	parse_player(char *filename, t_player *player)
{
	int		fd;
	t_header	*player_header;

	player_header = &player->header;
	if ((fd = open_file(filename)) == FAILURE)
		return (FAILURE);
	if (read_magic(filename, fd, player_header) == FAILURE
			|| read_name(filename, fd, player_header) == FAILURE
			|| read_zero_block(filename, fd) == FAILURE
			|| read_prog_size(filename, fd, player_header) == FAILURE
			|| read_comment(filename, fd, player_header) == FAILURE
			|| read_zero_block(filename, fd) == FAILURE
			|| read_prog(filename, fd, player) == FAILURE)
	{
		close_fd(fd);
		return (FAILURE);
	}
	return (close_fd(fd));
}

t_ex_ret	manage_player(char *filename, t_vm *vm, int num)
{
	t_player	*player;

	if (vm->players_number + 1 > MAX_PLAYERS)
		return (max_player_err());
	vm->players_number += 1;
	player = &vm->player[vm->players_number - 1];
	player->num = num;
	if (parse_player(filename, player) == FAILURE)
		return (FAILURE);
	/*print_player(player); //DEBUG*/
	return (SUCCESS);
}
