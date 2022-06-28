#!/usr/local/bin/python3
# -*- coding: utf-8 -*-

import re
pattern = r"spam"
if re.match(pattern, "spamspamspam"):
    print("Match")
else:
    print("Not Match")

if re.match(pattern, "eggspamsausagespam"):
    print("match")
else:
    print("not match")

if re.search(pattern, "eggspamsausagespam"):
    print("match")
else:
    print("not match")

print(re.findall(pattern, "eggspamsausagespam"))

pattern = r"pam"
match = re.search(pattern, "eggspamsausagespam")
if match:
    print(match.group())
    print(match.start())
    print(match.end())
    print(match.span())

str = "My name is David. Hi David"
pattern = r"David"
newstr = re.sub(pattern, "Amy", str)
print(newstr)
