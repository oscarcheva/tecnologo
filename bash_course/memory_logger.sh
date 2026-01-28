#!/bin/bash

if [ -d  "/$HOME/performance" ] ; then
	echo "Folder Exists!"
else
	mkdir "/$HOME/performance"
	echo "Folder not exists, creating"
fi

free >> "/$HOME/performance/memory.log"
