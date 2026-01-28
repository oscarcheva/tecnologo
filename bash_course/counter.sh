#!/bin/bash

while getopts "m:s:" opt;
do
	case "$opt" in
		m) seconds=$(($OPTARG * 60));;
		s) seconds=$OPTARG;;
		\?) echo "Invalid choice";;
	esac

done
while [ $seconds -ge 0 ]; 
do
	echo $seconds
	seconds=$(($seconds - 1))
	sleep 0.02
done
