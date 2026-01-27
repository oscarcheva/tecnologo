#!/bin/bash

PS3="Please select the type of phone: "
select type in Headset Handheld
do
	break
done
PS3="Please select the department "
select dept in Finance Sales "Customer service" Engineering
do
	break
done
read -p "Enter first name: " name
read -p "Enter surname: " surname
read -p "Enter extension number: " extension
read -s -N 4 -p "Enter access code: " code
echo ""

echo $name,$surname,$extension,$code,$type,$dept >> extensions.csv



