#!/usr/local/bin/python3
# -*- coding: utf-8 -*-


class MyClass():
    n = 0

    def __init__(self):
        MyClass.n += 1

    def __del__(self):
        MyClass.n -= 1


a = MyClass()
print(a.n)
b = MyClass()
print(b.n)
a = MyClass()
print(a.n)
