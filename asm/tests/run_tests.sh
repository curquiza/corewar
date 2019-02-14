#!/bin/bash

FILE="./asm"
DIR_TEST="tests"
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

echo "*** No such file or directory: " > $TRACE
run_test "No such file or directory: " "$($FILE toto.s 2>&1 | tee -a $TRACE)" "Error: toto.s: No such file or directory."

echo "
*** Permission denied: " >> $TRACE
chmod 000 $DIR_TEST/perm_denied.s
run_test "Permission denied: " "$($FILE $DIR_TEST/perm_denied.s 2>&1 | tee -a $TRACE)" "Error: $DIR_TEST/perm_denied.s: Permission denied."
chmod 755 $DIR_TEST/perm_denied.s

echo "
*** Illegal option: " >> $TRACE
run_test "Illegal option: " "$($FILE -z toto 2>&1 | tee -a $TRACE)" "asm: illegal option
usage: ./asm [-a] <src_file.s>
	-a: writes an annotated version of the code to stdout."

echo "
*** Wrong extension: " >> $TRACE
run_test "Wrong extension: " "$($FILE $DIR_TEST/file.wrong_ext.coco 2>&1 | tee -a $TRACE)" "usage: ./asm [-a] <src_file.s>
	-a: writes an annotated version of the code to stdout."
