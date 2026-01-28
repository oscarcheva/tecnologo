#!/bin/bash

for element in first second third; do
	echo "This is $element"
done

readarray -t day < days.txt
for days in "${day[@]}"; do
	if [ -f  "$days.txt" ]; then
		echo "File "$days.txt" already exists"
	else
		touch "$days.txt"
		echo "File "$days.txt" created"
	fi
done
