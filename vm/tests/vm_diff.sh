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
trace="tests/vm_diff_trace.txt"

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
			echo "file : $1 - step : $i" >> $trace
		fi
	done
}

rm -f $trace

if [[ ! -f $corewar_bin ]] || [[ ! -f $zaz_corewar_bin ]]; then
	echo "Error: corewar binary not found." 1>&2
	exit 1
fi

tests_folder="tests/input_basics"
run_test "and_1.cor"							0 500   1500	# end : 1536
run_test "st_1.cor"								0 500   1500	# end : 1536
run_test "sti_1.cor"							0 500   1500	# end : 1536
run_test "sti_2.cor"							0 500   1500	# end : 1536
run_test "sti_3.cor"							0 500   1500	# end : 1536
run_test "sti_4.cor"							0 500   1500	# end : 1536
run_test "st_30.cor"							0 500   3000	# end : 3072
run_test "zjmp_1.cor"							0 500   1500	# end : 1536
run_test "zjmp_2.cor"							0 1000  3000	# end : 3072
run_test "zjmp_3.cor"							0 500   1500	# end : 1536
run_test "fork_2.cor"							0 500   1500	# end : 1536
run_test "lfork.cor"							0 500   1500	# end : 1536
#run_test "lld2.cor"							0 500   1500	# end : 1536 FAIL 35 -> BUG ??? dlaurent aussi
run_test "lldi.cor"								0 500   1500	# end : 1536
run_test "ld_st_overflow.cor"					0 500   1500	# end : 1536
run_test "ldi_bug_in_zaz_corewar.cor"			0 500   1500	# end : 1536
run_test "ldi_test.cor"							0 500   1500	# end : 1536
run_test "adv_null.cor"							0 500   1500	# end : 1536
run_test "carry.cor"							0 500   1500	# end : 1536
run_test "empty_namecomment.cor"				0 1000  3000	# end : 3072
run_test "end_comment.cor"						0 500   1500	# end : 1536
run_test "flipped_name_comment.cor"				0 500   1500	# end : 1536
run_test "hash_and_tab_at_EOF.cor"				0 1000  3000	# end : 3072
run_test "hash_at_header.cor"					0 1000  3000	# end : 3072
run_test "neg_indirect_error.cor"				0 500   1500	# end : 1536
run_test "negative_st.cor"						0 500   1500	# end : 1536
run_test "nl_at_header.cor"						0 1000  3000	# end : 3072
run_test "nl_at_header_flipped.cor"				0 1000  3000	# end : 3072
run_test "no_space_between_op_and_param.cor"	0 1000  3000	# end : 3072
run_test "op_code_unknown.cor"					0 60000 240000	# end : 243336
run_test "process_next_pc_overflow.cor"			0 500   1500	# end : 1536
run_test "reg_after_fork.cor"					0 500   1500	# end : 1536
run_test "sq_at_header.cor"						0 1000  3000	# end : 3072
run_test "t.cor"								0 500   1500	# end : 1536
run_test "tab_at_end_of_file.cor"				0 1000  3000	# end : 3072
run_test "test_life.cor"						0 1000  3000	# end : 3072
run_test "test_lifeX.cor"						0 1000  3000	# end : 3072
run_test "test_limit.cor"						0 1000  3000	# end : 3072
run_test "test_no_life.cor"						0 500   1500	# end : 1536
run_test "test_ocp.cor"							0 500   1500	# end : 1536
run_test "test_process_1.cor"					0 1000  3000	# end : 3072
run_test "test_process_2.cor"					0 500   1500	# end : 1536
run_test "test_with_many_live.cor"				0 1000  3000	# end : 3072
run_test "testing1.cor"							0 1000  3000	# end : 3072
run_test "testing2.cor"							0 1000  3000	# end : 3072
run_test "testing_reg_after_fork.cor"			0 500   1500	# end : 1536
run_test "try.cor"								0 500   1500	# end : 1536
run_test "weirdest_error_ever.cor"				0 1000  3000	# end : 3072
run_test "wrong_ocp.cor"						0 1000  3000	# end : 3072

tests_folder="tests/input_champs"
run_test "Asombra.cor"					0 10000 30000	# end : 30360
run_test "Car.cor"						0 2000  14000	# end : too long
run_test "Douceur_power.cor"			0 9100  27400	# end : 27438
run_test "Explosive_Kitty.cor"			0 3920  39200	# end : 39218
run_test "Gagnant.cor"					0 2600  26000	# end : 26024
run_test "Kappa.cor"					0 2590  25900	# end : 25902
run_test "Kittystrophic.cor"			0 10000 110000	# end : 116172
run_test "Machine-gun.cor"				0 1000  3000	# end : 3072
run_test "MarineKing.cor"				0 2740  27400	# end : 27438
run_test "Misaka_Mikoto.cor"			0 2780  27800	# end : 27849
run_test "Octobre_Rouge_V4.2.cor"		0 2740  27400	# end : 27438
run_test "Rainbow_dash.cor"				0 8330  83300	# end : 83334
run_test "Survivor.cor"					0 1000  3000	# end : 3072
run_test "THUNDER.cor"					0 5260  52600	# end : 52680
run_test "Varimathras.cor"				0 5260  52600	# end : 76224
run_test "Wall.cor"						0 2740  27400	# end : 27438
run_test "_.cor"						0 2740  27400	# end : 27439
run_test "_honeybadger.cor"				0 500   1500	# end : 1536
run_test "azork.cor"					0 5790  57900	# end : 57955
run_test "azorkX.cor"					0 5790  57900	# end : 57955
run_test "bee_gees.cor"					0 27000 27000	# end : 27438
run_test "big_feet.cor"					0 5100  25900	# end : 25902
run_test "bigzork.cor"					0 4000  28000	# end : 28363
run_test "casimir.cor"					0 2800  28000	# end : 28162
run_test "champ.cor"					0 24100 241000	# end : 241760
run_test "corelol.cor"					0 5790  57900	# end : 57954
run_test "darksasuke.cor"				0 3200  32000	# end : 32022
run_test "doge.cor"						0 2620  26200	# end : 26226
run_test "dubo.cor"						0 1000  3000	# end : 3072
run_test "ex.cor"						0 1000  3000	# end : 3072
run_test "ex1.cor"						0 1000  3000	# end : 3072
run_test "exe_order.cor"				0 500   1500	# end : 1500
run_test "exe_order2.cor"				0 1000  3000	# end : 3072
run_test "fluttershy.cor"				0 5000  25000	# end : 25903
run_test "gateau.cor"					0 2900  29000	# end : 29010
run_test "gedeon.cor"					0 5000  25000	# end : 25903
run_test "helltrain.cor"				0 9100  27400	# end : 27439
run_test "jinx.cor"						0 6000  24000	# end : 24266
run_test "jumper.cor"					0 6000  24000	# end : 24690
run_test "justin_bee.cor"				0 2700  27000	# end : 27000
run_test "littlepuppy.cor"				0 1000  3000	# end : 3072
run_test "live.cor"						0 5100  20400	# end : 20440
run_test "loose.cor"					0 2900  29000	# end : 29238
run_test "mandragore.cor"				0 5000  15000	# end : too long
run_test "maxidef.cor"					0 2590  25900	# end : 25902
run_test "meowluigi.cor"				0 2740  27400	# end : 27439
run_test "mise_a_jour_windows95.cor"	0 13700 27400	# end : 27439
run_test "mortel.cor"					0 1000  7400	# end : 7430
run_test "overwatch.cor"				0 2740  27400	# end : 27439
run_test "run_Kitty_RUN.cor"			0 12700 127000	# end : 127190
run_test "salamahenagalabadoun.cor"		0 1000  3000	# end : 3072
run_test "sam_2.0.cor"					0 10000 100000	# end : 111226
run_test "skynet.cor"					0 2590  25900	# end : 25900
run_test "slider2.cor"					23373 1 23374	# end : 25200 FAIL 23373
run_test "terminator.cor"				0 2270  22700	# end : 22756
run_test "toto.cor"						0 6500  26000	# end : 26024
run_test "turtle.cor"					0 4000  40000	# end : 40481
run_test "ultima.cor"					0 2820  28200	# end : 28224
run_test "ultimate-surrender.cor"		0 1000  3000	# end : 3072
run_test "ultimate.cor"					0 460   4600	# end : 4608
run_test "youforkmytralala.cor"			0 12000 24000	# end : 24828
run_test "zork.cor"						0 5000  57000	# end : 57955
run_test "zultimate-surrender.cor"		0 1000  3000	# end : 3072

#tests_folder="tests/input_champs"
#for file in "$tests_folder"/*.cor ; do
  #name="$(basename "$file")"
  #run_test "$name" 0 500 3500
#done

#tests_folder="tests/input_dlaurent_unitests"
#for file in "$tests_folder"/*.cor ; do
#   name="$(basename "$file")"
#   run_test "$name" 0 500 1500
#done
# FAIL : lld2.cor
# dlaurent : lld.cor lld2.cor

#tests_folder="tests/input_dlaurent_compiled"
#for file in "$tests_folder"/*.cor ; do
   #name="$(basename "$file")"
   #run_test "$name" 0 500 1500
#done

exit $status
