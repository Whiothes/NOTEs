#!/bin/bash
# Program:
#   Use function to repeat information.
# History:
#   2017-02-13 zhoush 1st release
PATH=${PATH}:/home/zhoush/Srcs/Practice/vbird_linux_basic/Chapter12
export PATH

printit(){
    echo -n "Your choice is " # 加-n可以不断行继续在同一行显示
}

echo "This program will print your selection!"
case ${1} in
    "one")
        printit; echo ${1} | tr 'a-z' 'A-z' # 参数做大小写转换
        ;;
    "two")
        printit; echo ${1} | tr 'a-z' 'A-Z'
        ;;
    "three")
        printit; echo ${1} | tr 'a-z' 'A-Z'
        ;;
    *)
        echo "Usage ${0} {one | two | three}"
esac
