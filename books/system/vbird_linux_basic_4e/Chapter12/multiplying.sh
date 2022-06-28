#!/bin/bash
# Program:
#   User inputs 2 integer numbers; program will cross these two numbers;
# History:
#  Mon Feb 13 13:13:51 CST 2017
PATH=${PATH}:/home/zhoush/Srcs/Practice/vbird_linux_basic/Chapter12
export PATH

echo -e "You should input 2 numbers, I will multiplying them!\n"
read -p "1st number: " fstnu
read -p "2rd number: " secnu
total=$((${fstnu}*${secnu}))
echo -e "\nThe result of ${fstnu} * ${secnu} == ${total}"
