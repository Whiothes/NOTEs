#!/usr/local/bin/python3

import os
import time

# 1. The files and directories to be backed up are
# specified in a list
# Example on Mac OS X and Linux:
source = [
    "/Users/zhoush/Documents/Private/Notes/books/python/A Byte of Python/list"
]

# 2. The backup must be stored in a
# main backup directory
# Example On Mac OS X and Linux:
target_dir = "/Users/zhoush/"

# 3. The files are backed up into a 7z file
# 4. The name of the 7z archive is the current date and time
target = target_dir + time.strftime('%Y%m%d%H%M%S') + '.7z'

# create target directory if it is not present
if not os.path.exists(target_dir):
    os.mkdir(target_dir)  # make directory

# 5. We use the 7z command to put the files in a 7z archive
p7zip_command = '7z a {0} {1}'.format(target, ' '.join(source))

# Run the backup
print('p7zip command is :')
print(p7zip_command)
print("Running:")
if os.system(p7zip_command) == 0:
    print('Successful backup to ', target)
else:
    print('Backup FAILED')
