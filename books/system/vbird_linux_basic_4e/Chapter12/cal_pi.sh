#!/bin/bash
# Program:
#   User input a scale number to calculate pi number.
# History:
#  Mon Feb 13 13:13:51 CST 2017
PATH=${PATH}:/home/zhoush/Srcs/Practice/vbird_linux_basic/Chapter12
export PATH

echo -e "This program will calculate pi value.\n"
read -p "You should input a float number to calculate pi value.\n"
read -p "The scale number(10~10000)?" checking
num=${checking:-"10"}             # set value=10 if no value was set
time echo "scale=${num}; 4 * a(1)"|bc -lq
