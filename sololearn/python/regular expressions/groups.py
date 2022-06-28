#!/usr/local/bin/python3

# -*- coding: utf-8 -*-
import re

# pattern = r"a(bc)(de)(f(g)h)i"

# match = re.match(pattern, "abcdefghijklmnop")
# if match:
#     print(match.group())
#     print(match.group(0))
#     print(match.group(1))
#     print(match.group(2))
#     print(match.groups())

pattern = r"(?P<first>abc)(?:def)(ghi)"

match = re.match(pattern, "abcdefghi")
if match:
    print(match.group("first"))
    print(match.groups())
