
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"

/*
 * MAIN GOAL :
 * Recreer zork.cor identique à celui générer par le binaire asm de zaz
 */

void write_n_zero_bytes(int fd, int n)
{
	while (n > 0)
	{
		ft_putchar_fd(0x00, fd);
		n--;
	}
}

int main (void)
{
	int fd;

	fd = open("test.cor", O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	/* magic */
	ft_putchar_fd(0x00, fd);
	ft_putchar_fd(0xea, fd);
	ft_putchar_fd(0x83, fd);
	ft_putchar_fd(0xf3, fd);
	/* name */
	ft_putchar_fd(0x7a, fd);
	ft_putchar_fd(0x6f, fd);
	ft_putchar_fd(0x72, fd);
	ft_putchar_fd(0x6b, fd);
	write_n_zero_bytes(fd, 128 - 4 + 6); /* + 6 ??? */
	/* comment */
	ft_putchar_fd(0x00, fd);
	ft_putchar_fd(0x17, fd);
	ft_putchar_fd(0x49, fd);
	ft_putchar_fd(0x27, fd);
	ft_putchar_fd(0x4d, fd);
	ft_putchar_fd(0x20, fd);
	ft_putchar_fd(0x41, fd);
	ft_putchar_fd(0x4c, fd);
	ft_putchar_fd(0x49, fd);
	ft_putchar_fd(0x49, fd);
	ft_putchar_fd(0x49, fd);
	ft_putchar_fd(0x49, fd);
	ft_putchar_fd(0x56, fd);
	ft_putchar_fd(0x45, fd);
	write_n_zero_bytes(fd, 2048 - 14 + 6); /* + 6 ??? */
	/* instructions */
	ft_putchar_fd(0x0b, fd);
	ft_putchar_fd(0x68, fd);
	ft_putchar_fd(0x01, fd);
	ft_putchar_fd(0x00, fd);
	ft_putchar_fd(0x0f, fd);
	ft_putchar_fd(0x00, fd);
	ft_putchar_fd(0x01, fd);
	ft_putchar_fd(0x06, fd);
	ft_putchar_fd(0x64, fd);
	ft_putchar_fd(0x01, fd);
	ft_putchar_fd(0x00, fd);
	ft_putchar_fd(0x00, fd);
	ft_putchar_fd(0x00, fd);
	ft_putchar_fd(0x00, fd);
	ft_putchar_fd(0x01, fd);
	ft_putchar_fd(0x01, fd);
	ft_putchar_fd(0x00, fd);
	ft_putchar_fd(0x00, fd);
	ft_putchar_fd(0x00, fd);
	ft_putchar_fd(0x01, fd);
	ft_putchar_fd(0x09, fd);
	ft_putchar_fd(0xff, fd);
	ft_putchar_fd(0xfb, fd);

	return (0);
}
