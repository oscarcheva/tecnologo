#!/bin/bash

## Author: Oscar Echeverria
## Date Created: Jan 28, 2026
## Last Modified: Jan 28, 2026
## Description: Script to choose either from the cleaner or the organizer
## Usage: Run ./folder_organizer.sh, select option 1 or 2.

select choice in Cleanup Organize;
do
	if [[ $choice == "Cleanup" ]] ; then
		scripts/cruft_remover.sh
	elif [[ $choice == "Organize" ]] ; then
		scripts/folder_organizer.sh
	else
		echo "Invalid choice"
	fi
break
done
