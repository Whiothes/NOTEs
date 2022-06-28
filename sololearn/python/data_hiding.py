#!/usr/local/bind/python3
# -*- coding: utf-8 -*-


class Queue:
    def __init__(self, contents):
        self._hiddenlist = list(contents)

    def push(self, value):
        self._hiddenlist.insert(0, value)

    def pop(self):
        self._hiddenlist.pop(-1)

    def __repr__(self):
        return "Queue({})".format(self._hiddenlist)


queue = Queue([1, 2, 3])
print("new:", queue)
queue.push(0)
print("after push:", queue)
queue.pop()
print("after pop:", queue)
print(queue._hiddenlist)


class Spam:
    __egg = 7

    def print_egg(self):
        print(self.__egg)


s = Spam()
s.print_egg()
print(s._Spam__egg)
print(s.__egg)
