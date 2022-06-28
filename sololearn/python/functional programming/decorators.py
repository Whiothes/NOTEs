#!/usr/local/bind/python3
# -*- coding: utf-8 -*-


def decor(func):
    def wrap():
        print("=============")
        func()
        print("=============")

    return wrap


def decor1(func):
    def wrap():
        print("--------------")
        func()
        print("--------------")

    return wrap


def print_text():
    print("Hello world!")


# decorated = decor(print_text)
# decorated()


@decor
@decor1
def print_text():
    print("***********")
    print("Hello world")
    print("***********")


print_text()
