#!/usr/local/bin/python3
# -*- coding: utf-8 -*-

from itertools import count, cycle, repeat

# count
for i in count(3):
    print(i)
    if i >= 11:
        break

# cycle
str = "python"
j = 0
for i in cycle(str):
    print(i)
    j += 1
    if j >= 30:
        break
# repeat
print(list(repeat(str, 3)))

from itertools import accumulate, takewhile, chain

nums = list(accumulate(range(8)))
print(nums)
print(list(takewhile(lambda x: x <= 6, nums)))
print(list(chain([1, 3, 5, 7, 9], [2, 4, 6, 8, 10])))

from itertools import product, permutations
letters = ("A", "B")
print(list(product(letters, range(2))))
print(list(permutations(letters)))
