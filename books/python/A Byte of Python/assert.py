#!/usr/bin/env python3
# -*- coding: utf-8 -*-

try:
    a = None

    assert a is not None

    print("hello")

except AssertionError as e:
    print(e)
