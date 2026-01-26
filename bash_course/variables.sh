#!/bin/bash

name="OsCar"
number=0123456789
echo "$name"
echo "${name,}"
echo "${name,,}"
echo "${name^}"
echo "${name^^}"
echo "${#name}"
echo "${number:1:5}"
echo "${number:3}"
echo "${number:2:}"
echo "${number: -3:2}"
