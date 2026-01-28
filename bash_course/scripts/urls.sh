#!/bin/bash

readarray -t urls < urls/urls.txt

for url in "${urls[@]}" ; do
	filename=$(echo "$url" | cut -d "." -f 2)
	curl -I "$url" >> urls/"$filename".txt
done


