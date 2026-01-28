#!/bin/bash

read -p "Enter a number: " number

case "$number" in
	[0-9]) 
		echo "Single number";;
	[0-9][0-9]) 
		echo "Double number";;
	[0-9][0-9][0-9]) 
		echo "Triple number";;
	*) echo "Some other kind of number";;
esac
