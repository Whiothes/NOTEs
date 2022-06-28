# -*- coding: utf-8 -*-


class Rectangle:
    def __init__(self, width, height):
        self.width = width
        self.height = height

    def calculate_sub(self):
        return self.height - self.width

    def calculate_area(self):
        return self.width * self.height

    @classmethod
    def new_square(classmethod, side_length):
        return classmethod(side_length, side_length)


square = Rectangle.new_square(5)
print(square.calculate_area())
