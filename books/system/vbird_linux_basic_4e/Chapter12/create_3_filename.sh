#!/bin/bash
# Program:
#   Program creates three files, which named by user's input and date command
# History:
# Sun Feb 12 17:56:35 CST 2017

PATH=${PATH}:/home/zhoush/Srcs/Practice/vbird_linux_basic/Chapter12
export PATH

# 1. 让使用者输入文件名, 并取得fileuser变量
echo -e "I will use 'touch' command to create 3 files." # 纯粹显示信息
read -p "Please input you filename: " fileuser          # 提示使用者输入

# 2. 避免使用者随意按Enter, 利用[变量功能]分析文件名是否设置
filename=${fileuser:-"filename"}                        # 开始判断是否有配置文件名

# 3. 开始利用date指令来获取所需要的文件名
date1=$(date --date='2 days ago' +%Y%m%d);
date2=$(date --date='1 days ago' +%Y%m%d);
date3=$(date +%Y%m%d);

file1=${filename}_${date1}
file2=${filename}_${date2}
file3=${filename}_${date3}
# 4. 创建文件
touch "${file1}"
touch "${file2}"
touch "${file3}"
