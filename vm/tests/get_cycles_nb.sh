#!/bin/bash

function basename() {
	local s="$1"
	echo "${s##*/}"
}

for file in tests/input_dlaurent_compiled/*.cor; do
	basename="$(basename "$file")"
	if [[ "$basename" != "Car.cor" ]] && [[ "$basename" != "mandragore.cor" ]]; then
		cycles="$(sh zaz_corewar.sh $file -v 2 | grep "It is now cycle" | tail -1 | cut -d ' ' -f5)"
		echo "$basename: $cycles"
	fi
done
