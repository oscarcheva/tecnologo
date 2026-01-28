#!/bin/bash

while read line;
do
	mkdir "$1"/"$line"
done < "files_to_create.txt"
