#!/bin/bash

FILE="./asm"
DIR_TEST="tests/input"
TRACE="tests/trace.txt"

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

echo "No such file or directory: " >> $TRACE
run_test "No such file or directory: " "$($FILE toto 2>&1 | tee $TRACE)" "Error: toto: No such file or directory."

echo "Permission denied: " >> $TRACE
chmod 000 $DIR_TEST/perm_denied
run_test "Permission denied: " "$($FILE $DIR_TEST/perm_denied 2>&1 | tee $TRACE)" "Error: tests/input/perm_denied: Permission denied."
chmod 755 $DIR_TEST/perm_denied

echo "Illegal option: " >> $TRACE
run_test "Illegal option: " "$($FILE -z toto 2>&1 | tee $TRACE)" "asm: illegal option
usage: ./asm [-a] <sourcefile.s>
	-a : Instead of creating a .cor file, outputs a stripped and annotated version of the code to the standard output"
