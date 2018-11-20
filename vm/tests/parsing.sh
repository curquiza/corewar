#!/bin/bash

GREEN="\033[1;32m"
RED="\033[1;31m"
YELLOW="\x1b[33m"
DEF="\033[0m"

corewar_bin="./corewar"
input_path="./tests/input_parsing"
trace="./tests/parsing_trace.txt"

header_err="Error: wrong header format\n"
prog_size_err="Error: prog size in header differs from the real prog size\n"
player_num_err="Error: player number must be an integer value\n"
too_many_champ_err="Error: too many champions\n"

no_such_file_err() { echo "Open error: $1: No such file or directory\n"; }
wrong_flag_err() { echo "Error: $1: Not an available flag\n"; }

# Usage: print_rslt "subtitle" "result"
function print_rslt(){
	if [[ "$2" == "" ]]; then
		printf "%-50s$GREEN%s$DEF\n" "$1" "✓"
	else
		printf "%-50s$RED%s$DEF\n" "$1" "✕"
		echo "$1" ":" >> $trace
		echo "$2" >> $trace
		echo "---------------------------" >> $trace
	fi
}

# Usage: run_test "all_options" "output_expected" "optionnal_subtitle"
function run_test() {
	$corewar_bin $1 > output1 2>&1
	printf "$2" > output2
	local rslt="$(diff output1 output2)"
	if [[ "$3" == "" ]]; then
		print_rslt "$1" "$rslt"
	else
		print_rslt "$3" "$rslt"
	fi
}

rm -f $trace

if [[ ! -f $corewar_bin ]]; then
	echo "Error: corewar binary not found." 1>&2
	exit 1
fi

run_test "." "Read error: .: Is a directory\n"
run_test "coco" "$(no_such_file_err "coco")"
run_test "-" "$(no_such_file_err "-")"
run_test "$input_path/wrong_magic.cor" "$header_err"
run_test "$input_path/name_cut.cor" "$header_err"
run_test "$input_path/name_cut2.cor" "$header_err"
run_test "$input_path/wrong_name_end.cor" "$header_err"
run_test "$input_path/size_cut.cor" "$header_err"
run_test "$input_path/comment_cut.cor" "$header_err"
run_test "$input_path/comment_cut2.cor" "$header_err"
run_test "$input_path/wrong_comment_end.cor" "$header_err"
run_test "$input_path/wrong_progsize.cor" "$prog_size_err"
run_test "$input_path/wrong_progsize2.cor" "$prog_size_err"
run_test "-n 12" "Open error: : Bad address\n"
run_test "-n" "$player_num_err"
run_test "-n 1111111111111111111111" "$player_num_err"
run_test "-n 2147483648" "$player_num_err"
run_test "-n 2247483647" "$player_num_err"
run_test "-n -2147483649" "$player_num_err"
run_test "-n -2157483648" "$player_num_err"
run_test "-n 1a" "$player_num_err"
run_test "-n --01" "$player_num_err"
run_test "tests/input_parsing/zork.cor tests/input_parsing/zork.cor tests/input_parsing/zork.cor tests/input_parsing/zork.cor tests/input_parsing/zork.cor" \
			"$too_many_champ_err" \
			"< 5 champions >"
run_test "tests/input_parsing/zork.cor -n 1 tests/input_parsing/zork.cor tests/input_parsing/zork.cor -n -1 tests/input_parsing/zork.cor tests/input_parsing/zork.cor" \
			"$too_many_champ_err" \
			"< 5 champions with -n flags >"
run_test "-titi" "$(wrong_flag_err "-titi")"
run_test "-n 1 -titi" "$(no_such_file_err "-titi")"
run_test "-n 1 $input_path/zork.cor -t" "$(wrong_flag_err "-t")"

rm -f output1 output2
