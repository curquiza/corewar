#include "asm.h"

unsigned int        ft_swap_int(unsigned int n)
{
    unsigned int    swap;

    swap = ((n >> 24) & 0xFF)\
    | ((n >> 8) & 0xFF00)\
    | ((n << 8) & 0xFF0000)\
    | ((n << 24) & 0xFF000000);
    return (swap);
}

unsigned short     ft_swap_short(unsigned short n)
{
    unsigned short     swap;

    swap = ((n >> 8) & 0xFF)\
    | ((n << 8) & 0xFF00);
    return (swap);
}