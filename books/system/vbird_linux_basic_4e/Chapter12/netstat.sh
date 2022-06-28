#!/bin/bash
# Program:
#     Using netstat and grep to detect WWW,SSH,FTP and Mail services.
# History:
# 2015/07/16    VBird    First release
PATH=${PATH}:/home/zhoush/Srcs/Practice/vbird_linux_basic/Chapter12
export PATH

# 1. 先做一些告知的动作
echo "Now, I will detect your Linux server's services"
echo -e "The www, ftp, ssh, and mail(smtp)will be detected! \n"

# 2. 开始进行一些测试的工作,并且也输出一些信息
testfile=/home/zhoush/Srcs/Practice/vbird_linux_basic/Chapter12/netstat_checking.txt
netstat -tuln > ${testfile}              # 先转存数据到内存中, 不用一直执行netstat

testing=$(grep ":80" ${testfile})

if [ -n "$testing" ]; then
    echo "WWW is running in your system."
fi

testing=$(grep ":22" ${testfile})
if [ -n "$testing" ]; then
    echo "SSH is running in your system."
fi

testing=$(grep ":21" ${testfile})
if [ -n "$testing" ]; then
    echo "FTP is running in your system."
fi

testing=$(grep ":25" ${testfile})
if [ -n "$testing" ]; then
    echo "MAIL is running in your system."
fi
