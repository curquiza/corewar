#include "vm.h"

static t_ex_ret	parse_player(char *filename, t_player *player)
{
	int		fd;
	t_header	*player_header;

	player_header = &player->header;
	if ((fd = open_file(filename)) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (read_magic(filename, fd, player_header) == EXIT_FAILURE
			|| read_name(filename, fd, player_header) == EXIT_FAILURE
			|| read_zero_block(filename, fd) == EXIT_FAILURE
			|| read_prog_size(filename, fd, player_header) == EXIT_FAILURE
			|| read_comment(filename, fd, player_header) == EXIT_FAILURE
			|| read_zero_block(filename, fd) == EXIT_FAILURE
			|| read_prog(filename, fd, player) == EXIT_FAILURE)
	{
		close_fd(fd);
		return (EXIT_FAILURE);
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
	if (parse_player(filename, player) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	/*print_player(player); //DEBUG*/
	return (EXIT_SUCCESS);
}
