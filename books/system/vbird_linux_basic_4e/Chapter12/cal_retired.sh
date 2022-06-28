#!/bin/bash
# Program:
#    You input your demobilization date, I calculate how many days before you demobilize.
# History:
#   2017-02-13 zhoush 1st release

PATH=${PATH}:/home/zhoush/Srcs/Practice/vbird_linux_basic/Chapter12
export PATH

# 1. 告知使用者这个程序的用途, 并且告知应该如何输入日期格式
echo "This program will try to calculate: "
echo "How many days before your demobilization date ... "
read_date(){
    read -p "Please input your demobilization date(YYYYMMDD): " udate
}

# 2. 测试一下, 这个输入的内容是否正确, 利用正则表达式
read_date;
check=$(echo ${udate} | grep '[[:digit:]]\{8\}')
if [ "$check" == "" ]; then
    echo "You input the wrong date format, try again. \n"
    read_date
fi

# 3. 开始计算日期
declare -i date_dem=$(date --date="${udate}" +%s)# 退伍日期秒数
declare -i date_now=$(date +%s)# 现在日期秒数
declare -i date_total_s=$((${date_dem} - ${date_now}))# 剩余秒数
declare -i date_d=$((${date_total_s}/60/60/24))# 转为日期
if [ "${date_total_s}" -lt "0" ]; then                  # 判断是否已退伍
    echo "You had been demobilization before: " $((-1*${date_d}))" ago"
else
    declare -i date_h=$(($((${date_total_s}-${date_d}*60*60*24))/60/60))
    echo "You will demobilize after ${date_d} days and ${date_h} hours."
fi
