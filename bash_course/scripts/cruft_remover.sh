#!/bin/bash

## Author: Oscar Echeverria
## Date Created: Jan 28, 2026
## Last Modified: Jan 28, 2026
## Description: Script to remove files in a specified folder that haven't been used since N days.
## Usage: Run ./cruft_remover.sh, then when prompted specify the folder and the days.

read -p "Please enter the path to be deleted: " path
read -p "Please enter the number of days: " days

readarray -t files < <(find "$path" -mtime "$days")

for file in "${files[@]}"; do
	echo $file
	rm -i $file
done
