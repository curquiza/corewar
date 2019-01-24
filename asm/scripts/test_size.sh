#!/bin/bash

DEF="\033[0m"
YELLOW='\033[0;33m'
GREEN='\033[0;32m'
RED='\033[0;31m'

OK=0
KO=0
# test_prog_size "file"
function test_prog_size () {

	./asm -a $1 | grep size > moi
	/Users/sarahfranc/sarah/corewar/resources/./asm -a $1 | grep size > zaz
	if [[ "$(cat zaz)" != "" && "$(cat zaz)" != "" && "$(cat zaz)" == "$(cat moi)" ]] ; then
		printf "${GREEN}OK${DEF}\n"
		OK=$((OK+1))
	else
		printf "${RED}KO${DEF}\n"
		KO=$((KO+1))
	fi
	rm moi zaz
}

# run_tests "path"
function run_tests () {

	for entry in `find $1 -type f -name "*.s"`
	do
		echo -n "test" $entry ": "
		test_prog_size $entry
	done

}

function main() {

	local path1="/Users/sarahfranc/sarah/corewar/resources/champs"

	run_tests $path1

	TOTAL=$((OK+KO))
	echo "OK:" $OK
	echo "KO:" $KO
	echo "---------------"
	echo "TOTAL:" $TOTAL

}
main "$@"
