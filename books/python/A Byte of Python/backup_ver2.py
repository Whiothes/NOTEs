#!/usr/bin/env python3
# -*- coding: utf-8 -*-

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

# create target directory if it is not present
if not os.path.exists(target_dir):
    os.mkdir(target_dir)  # make directory

# 3. The files are backed up into a 7z file
# 4. The current day is the name of the subdirectory
# in the main directory
today = target_dir + os.sep + time.strftime('%Y%m%d')
# The current time is the name of the 7z archieve.
now = time.strftime('%H%M%S')

# The name of the 7z file
target = today + os.sep + now + '.7z'

# Create the subdirectory if it isn't already there
if not os.path.exists(today):
    os.mkdir(today)
    print('Successfully created directory', today)

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
