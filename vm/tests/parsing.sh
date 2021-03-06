#!/bin/bash

GREEN="\033[1;32m"
RED="\033[1;31m"
YELLOW="\x1b[33m"
DEF="\033[0m"

corewar_bin="./corewar"
input_path="./tests/input_parsing"
trace="./tests/parsing_trace.txt"

header_err="Error: Wrong header format\n"
prog_size_err="Error: Header prog size differs from the real prog size\n"
player_num_err1="Error: 2 arguments are needed for -n flag\n"
player_num_err2="Error: Player number must be a positive integer value\n"
player_num_err3="Error: 2 players cannot have the same number\n"
dump_cycle_err1="Error: 1 argument is needed for -dump flag\n"
dump_cycle_err2="Error: Dump cycle must be a positive integer value\n"
too_many_champ_err="Error: Too many champions\n"
prog_size_too_large_err="Error: Prog size is too large\n"
verbose_err1="Error: 1 argument is needed for -verbose flag\n"
verbose_err2="Error: Not a valid argument for -verbose flag (1 or 2)\n"

status=0

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
		status=1
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
run_test "$input_path/prog_too_large.cor" "$prog_size_too_large_err"
run_test "-n" "$player_num_err1"
run_test "-n 12" "$player_num_err1"
run_test "-n 1111111111111111111111 coco" "$player_num_err2"
run_test "-n 2147483648 coco" "$player_num_err2"
run_test "-n 2247483647 coco" "$player_num_err2"
run_test "-n -21 coco" "$player_num_err2"
run_test "-n 1a coco" "$player_num_err2"
run_test "-n ++01 coco" "$player_num_err2"
run_test "-n --01 coco" "$player_num_err2"
run_test "-n 1 $input_path/zork.cor $input_path/zork.cor -n 1 $input_path/zork.cor" \
			"$player_num_err3" \
			"< 2 players with same number >"
run_test "$input_path/zork.cor $input_path/zork.cor $input_path/zork.cor $input_path/zork.cor $input_path/zork.cor" \
			"$too_many_champ_err" \
			"< 5 champions >"
run_test "tests/input_parsing/zork.cor -n 1 tests/input_parsing/zork.cor tests/input_parsing/zork.cor -n 0 tests/input_parsing/zork.cor tests/input_parsing/zork.cor" \
			"$too_many_champ_err" \
			"< 5 champions with -n flags >"
run_test "-titi" "$(wrong_flag_err "-titi")"
run_test "-n 1 -titi" "$(no_such_file_err "-titi")"
run_test "-n 1 $input_path/zork.cor -t" "$(wrong_flag_err "-t")"
run_test "--zaz" "$(wrong_flag_err "--zaz")"
run_test "-dump" "$dump_cycle_err1"
run_test "-dumpp " "$(wrong_flag_err "-dumpp")"
run_test "-dump x21" "$dump_cycle_err2"
run_test "-dump -21" "$dump_cycle_err2"
run_test "-dump 21 titi" "$(no_such_file_err "titi")"
run_test "-visu" "$(wrong_flag_err "-visu")"
run_test "-v" "$(wrong_flag_err "-v")"
run_test "-verbose" "$verbose_err1"
run_test "-verbose 12" "$verbose_err2"
run_test "-verbose coco.cor" "$verbose_err2"

rm -f output1 output2

exit $status
