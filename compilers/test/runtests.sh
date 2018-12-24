#!/bin/bash
for directory in ./tests/*; do
	echo "*** TESTING in $directory"
    for test in $directory/*; do
		echo "$test"
		if output=$(./while $test 2>&1); then
			echo "ok"
		else
			echo "err"
		fi
    done
done
