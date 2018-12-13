#!/bin/bash

GREEN="\033[1;32m"
RED="\033[1;31m"
YELLOW="\x1b[33m"
DEF="\033[0m"

corewar_bin="./corewar"
zaz_corewar_bin="../resources/corewar"
corewar="./corewar -zaz -dump"
zaz_corewar="../resources/corewar -d"
tests_folder="tests/input_instructions"

status=0

# Usage : check_diff "cycles" "file"
function check_diff() {
	$corewar "$1" "$2" | tail -n 64 > output1 2>&1
	$zaz_corewar "$1" "$2" | tail -n 64 > output2 2>&1
	local rslt="$(diff output1 output2)"
	rm -f output1 output2
	if [[ "$rslt" == "" ]]; then
		echo "1"
	else
		echo "0"
	fi
}

# Usage : run_test "file" "step" "cycle_max"
function run_test() {
	echo "$1"
	for i in $(seq 0 "$2" "$3"); do
		local rslt=$(check_diff "$i" "$tests_folder/$1")
		if [[ $rslt == "1" ]]; then
			printf "  > %-20s$GREEN%s$DEF\n" "$i" "✓"
		else
			printf "  > %-20s$RED%s$DEF\n" "$i" "✕"
			status=1
		fi
	done
}

if [[ ! -f $corewar_bin ]] || [[ ! -f $zaz_corewar_bin ]]; then
	echo "Error: corewar binary not found." 1>&2
	exit 1
fi

run_test "and_1.cor" 200 1500			# end : 1536
run_test "sti_1.cor" 200 1500			# end : 1536
run_test "sti_2.cor" 200 1500			# end : 1536
run_test "zjmp_1.cor" 200 1500			# end : 1536
run_test "zjmp_2.cor" 500 3000			# end : 3072
run_test "zork.cor" 1000 10000			# end : 57955

exit $status
