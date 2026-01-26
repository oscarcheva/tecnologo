#!/bin/bash

## Author: Oscar Echeverria
## Date Created: Jan 23, 2026
## Last Modified: Jan 23, 2026
## Description: Script to backup the home folder of the current user
## Usage: Run ./backup_script.sh

echo "Hello ${USER^}"
echo "I will now back up the directory where this script is being run"
currentdir=$(pwd)
echo "You are running this script from $currentdir and it will be saved here"
tar -cvf $currentdir/my_backup_"$(date +%d-%m-%Y_%H-%M-%S)".tar ~/* 2>/dev/null



exit 0
