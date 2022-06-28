#!/bin/bash
# Program:
#  use loop to calculate "1+2+3+...+100" result
# History:
#    2017-02-13  zhoush 1st release
PATH=${PATH}:/home/zhoush/Srcs/Practice/vbird_linux_basic/Chapter12
export PATH

s=0
i=0
while [ "${i}" != 100 ]; do
    i=$(($i+1))
    s=$(($s+$i))
done
echo "The result is: $s "
