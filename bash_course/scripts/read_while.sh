#!/bin/bash

while read line;
do
    echo "$line"
done < "$1"

while read line;
do
    echo "$line"
done < <(ls .)

