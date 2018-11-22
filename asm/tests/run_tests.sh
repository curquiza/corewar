#!/bin/bash

FILE="./asm"
DIR_TEST="tests/input"

OK="\033[92m"
FAIL="\033[91m"
END="\033[0m"
BOLD="\033[1m"

# run_test "name" "result" "expected" 

function run_test {

	local result="$2"
	local expected="$3"

	if [[ "$result" == "$expected" ]] ; then
		printf "%-30s$OK$BOLD%s$END\n" "$1" "OK"
	else
		printf "%-30s$FAIL$BOLD%s$END\n" "$1" "KO"
	fi
}

run_test "No such file or directory: " "$($FILE toto 2>&1)" "asm: toto: No such file or directory."

chmod 000 $DIR_TEST/perm_denied
run_test "Permission denied: " "$($FILE $DIR_TEST/perm_denied 2>&1)" "asm: tests/input/perm_denied: Permission denied."

run_test "Illegal option: " "$($FILE -z toto 2>&1)" "ft_nm: illegal option
usage: ./asm [-a] <sourcefile.s>
	-a : Instead of creating a .cor file, outputs a stripped and annotated version of the code to the standard output"
