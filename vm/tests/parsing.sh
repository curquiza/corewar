#!/bin/bash

GREEN="\033[1;32m"
RED="\033[1;31m"
YELLOW="\x1b[33m"
DEF="\033[0m"

corewar_bin="./corewar"
input_path="./tests/input_parsing"
trace="./tests/parsing_trace.txt"

# Usage: run_test "file" "output_expected"
function run_test() {
	$corewar_bin $1 > output1 2>&1
	printf "$2" > output2
	local rslt="$(diff output1 output2)"
	if [[ "$rslt" == "" ]]; then
		printf "%-50s$GREEN%s$DEF\n" "$1" "✓"
	else
		printf "%-50s$RED%s$DEF\n" "$1" "✕"
		echo $1 ":" >> $trace
		echo $rslt >> $trace
		echo "---------------------------" >> $trace
	fi
}

rm -f $trace

if [[ ! -f $corewar_bin ]]; then
	echo "Error: corewar binary not found." 1>&2
	exit 1
fi

run_test "." "Read error: .: Is a directory\n"
run_test "coco" "Open error: coco: No such file or directory\n"
run_test "$input_path/wrong_magic.cor" "Error: wrong header format\n"
run_test "$input_path/name_cut.cor" "Error: wrong header format\n"
run_test "$input_path/name_cut2.cor" "Error: wrong header format\n"
run_test "$input_path/wrong_name_end.cor" "Error: wrong header format\n"
run_test "$input_path/size_cut.cor" "Error: wrong header format\n"
run_test "$input_path/comment_cut.cor" "Error: wrong header format\n"
run_test "$input_path/comment_cut2.cor" "Error: wrong header format\n"
run_test "$input_path/wrong_comment_end.cor" "Error: wrong header format\n"
run_test "$input_path/wrong_progsize.cor" "Error: prog size in header differs from the real prog size\n"
run_test "$input_path/wrong_progsize2.cor" "Error: prog size in header differs from the real prog size\n"

rm -f output1 output2
