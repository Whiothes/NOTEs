# -*- coding: utf-8 -*-


def func(n):
    y = '*'.join(str(x) for x in range(1, n, 2))
    return eval(y)


print(func(7))
