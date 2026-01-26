#!/bin/bash

echo $((4 + 2))

one=6
two=10

echo "Sum $(( $one + $two ))"
echo "Substraction $(($one - $two))"
echo "Multiplication $(($one * $two))"
echo "Division $(($one / $two))"
echo "Power $((one**two))"

echo "10/2" | bc
echo "scale=2;5/2" | bc
