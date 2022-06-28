#!/bin/bash
# Program:
#   show the user's choice
# History:
#  Mon Feb 13 13:13:51 CST 2017
PATH=${PATH}:/home/zhoush/Srcs/Practice/vbird_linux_basic/Chapter12
export PATH

read -p "Please input(Y/N)" yn
[ "${yn}" == "Y" -o "${yn}" == "y" ] && echo "OK, continue" && exit 0;
[ "${yn}" == "N" -o "${yn}" == "n" ] && echo "Oh, interrupt" && exit 0;
echo "I don't know what your choice is " && exit 0;
