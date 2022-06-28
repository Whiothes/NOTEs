#!/usr/local/bin/python3
# -*- coding: utf-8 -*-

import re

pattern = r"(.+) \1"
print(re.findall(pattern, "word word"))

match = re.match(pattern, "word word")
if match:
    print("Match 1")

match = re.match(pattern, "?! ?!")
if match:
    print("Match 2")

match = re.match(pattern, "abc bcd")
if match:
    print("Match 3")
