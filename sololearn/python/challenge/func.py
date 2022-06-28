#!/usr/local/bin/python3
# -*- coding: utf-8 -*-


def func(number):
    return (number % 3 == 1 or number % 4 == 2)


a = list(range(10))
b = list(filter(func, a))
print(a)
print(b)

print("abcded".find("cd"))
print("cd" in "abcdef")

x = 5
while not x <= 6:
    x += 1
print(x + 2)


def tripper(orig_func):
    def my_function(orig_val):
        return (orig_func(orig_val) * 3)

    return (my_function)


@tripper
def doubler(user_input):
    return (user_input * 2)


def double(user_input):
    return (user_input * 2)


print(doubler(5))

from itertools import *
for i in count(20, -3):
    print(i)
    if i < 5:
        break
