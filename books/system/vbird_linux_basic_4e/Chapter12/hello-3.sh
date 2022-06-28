#!/bin/bash
# Program:
#     Show "Hello" from $1.... by using case .... esac
# History:
#   2017-02-13 zhoush 1st release
PATH=${PATH}:/home/zhoush/Srcs/Practice/vbird_linux_basic/Chapter12
export PATH


case ${1} in
    "hello")
        echo "Hello, how are you"
        ;;
    "")
        echo "You MUST input parameters, ex: ${${0} someword}"
        ;;
    *)
        echo "Usage ${0} {hello}"
        ;;
esac
