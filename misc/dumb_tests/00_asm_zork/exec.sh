#!/bin/bash

gcc -Wall -Wextra -Werror main.c -o asm -I ../../../libft/include ../../../libft/libft.a
ret_code=$?
if [ "$ret_code" = "0" ] ; then
	echo "Compilation done"
	./asm
	echo "Execution done"
	xxd test.cor > test_xxd
	xxd zork.cor > zork_xxd
	echo "Files created : test_xxd and zork_xxd"
else
	echo "Compilation failed"
fi
