# -*- coding: utf-8 -*-

list1 = [1, 2]
list2 = list1
list3 = list2[:]

print(list1)
print(list3)
print(list3 is list1)

a = [1, 2, 3, 4]
b = a[::-1]
c = b[::-2]
print(b)
print(c)

