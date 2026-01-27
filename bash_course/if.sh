#!/bin/bash


if [ $1 -eq $2 ]; then
	echo Test passed
elif [ $1 -gt $2 ]; then
	echo Other test passed
else
	echo Test failed
fi
