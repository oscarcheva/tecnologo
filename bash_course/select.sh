#!/bin/bash

PS3="What is the day of the week?: "
select choice in mon tue wed thu fri sat sun;
do
echo "The day is $choice"
break
done


