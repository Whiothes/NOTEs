#!/bin/bash
# Program:
#    Repeat question until user input correct answer.
# History:
#    2017-02-13  zhoush 1st release
PATH=${PATH}:/home/zhoush/Srcs/Practice/vbird_linux_basic/Chapter12
export PATH

until [ "${yn}" != 'yes' -a "${yn}" != "YES" ]; do
    read -p "Please input yes/YES to stop this program: " yn
done
echo "OK! you input the correct answer."
