#include "asm.h"
#include <fcntl.h>

int main (void)
{
	/*ft_putendl_fd("sortie 1", 1);*/
	/*ft_putendl_fd("Error line 0: No name found in the header.", 1);*/
	/*ft_putendl_fd("sortie 2", 2);*/
	open("tests/input/no_name.cor", O_CREAT);
	/*ft_strlen(NULL);*/
	return (0);
}
