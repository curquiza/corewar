#!/bin/bash

GREEN="\033[1;32m"
RED="\033[1;31m"
YELLOW="\x1b[33m"
DEF="\033[0m"

corewar_bin="./corewar"
#corewar_bin="../../dlaurent_corewar/vm/corewar"
zaz_corewar_bin="../resources/corewar"
corewar="$corewar_bin -zaz -dump"
#corewar="$corewar_bin --dump"
zaz_corewar="../resources/corewar -d"
tests_folder="tests/input_instructions"

status=0

function basename() {
	local s="$1"
	echo "${s##*/}"
}

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

# Usage : run_test "file" "begin" "step" "cycle_max"
function run_test() {
	echo "$1"
	for i in $(seq "$2" "$3" "$4"); do
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

tests_folder="tests/input_instructions"
run_test "and_1.cor"		0 500  1500		# end : 1536
run_test "st_1.cor"			0 500  1500		# end : 1536
run_test "sti_1.cor"		0 500  1500		# end : 1536
run_test "sti_2.cor"		0 500  1500		# end : 1536
run_test "sti_3.cor"		0 500  1500		# end : 1536
run_test "sti_4.cor"		0 500  1500		# end : 1536
run_test "st_30.cor"		0 500  3000		# end : 3072
run_test "zjmp_1.cor"		0 500  1500		# end : 1536
run_test "zjmp_2.cor"		0 1000 3000		# end : 3072
run_test "zjmp_3.cor"		0 500  1500		# end : 1536
run_test "fork_2.cor"		0 500  1500		# end : 1536
run_test "lfork.cor"		0 500  1500		# end : 1536
run_test "lld2.cor"			0 500  1500		# end : 1536 FAIL 35 -> BUG ??? dlaurent aussi
run_test "lldi.cor"			0 500  1500		# end : 1536 FAIL 75

tests_folder="tests/input_champs"
run_test "ex.cor"					0 1000 3000		# end : 3072
run_test "jumper.cor"				0 6000 24000	# end : 24690
run_test "maxidef.cor"				0 2590 25900	# end : 25902
run_test "mortel.cor"				0 1000 7400		# end : 7430
run_test "slider2.cor"				0 2520 25200	# end : 25200 FAIL
run_test "toto.cor"					0 6500 26000	# end : 26024
run_test "zork.cor"					0 5000 57000	# end : 57955
run_test "bigzork.cor"				0 4000 28000	# end : 28363
run_test "turtle.cor"				0 4000 40000	# end : 40481
run_test "fluttershy.cor"			0 5000 25000	# end : 25903
run_test "_.cor"					0 2740 27400	# end : 27439
run_test "Car.cor"					0 2000 14000	# end : too long
run_test "Gagnant.cor"				0 2600 26000	# end : 26024
run_test "Octobre_Rouge_V4.2.cor"	0 2740 27400	# end : 27438
run_test "helltrain.cor"			0 2740 27400	# end : 27439

#tests_folder="tests/input_dlaurent_unitests"
#for file in "$tests_folder"/*.cor ; do
	#name="$(basename "$file")"
	#run_test "$name" 0 500 1500
#done
# FAIL : ld_st_overflow.cor ldi_bug_in_zaz_corewar.cor lld2.cor lldi.cor
# dlaurent : lld.cor lld2.cor

#tests_folder="tests/input_dlaurent_compiled"
#for file in "$tests_folder"/*.cor ; do
	#name="$(basename "$file")"
	#run_test "$name" 0 1000 10000
#done

exit $status
