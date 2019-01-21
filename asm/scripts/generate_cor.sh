#!/bin/bash

DEF="\033[0m"
YELLOW='\033[0;33m'
GREEN='\033[0;32m'
RED='\033[0;31m'

ASM_ZAZ="/Users/sfranc/42/corewar/resources/./asm"

OK=0
TOTAL=0

# generate_cor "file"
function generate_cor () {

	$ASM_ZAZ $1 1> /dev/null 2> /dev/null
	if [[ "$?" == "0" ]]; then
		OK=$((OK+1))
		printf "${GREEN}OK${DEF}\n"
	else
		echo $1 >> failed_list.txt
		printf "${RED}KO${DEF}\n"
	fi
}

# run_tests "path"
function run_tests () {

	for entry in `find $1 -type f -name "*.s"`
	do	
		TOTAL=$((TOTAL+1))
		echo -n "compiling" $entry ": "
		generate_cor $entry
	done

}

function main() {

	local path1="/Users/sfranc/42/corewar/resources/champs"

	run_tests $path1

	echo "files generated: " $OK
	echo "---------------"
	echo "TOTAL:" $TOTAL

}
main "$@"
