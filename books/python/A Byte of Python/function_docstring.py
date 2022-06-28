def print_max(x, y):
    '''Prints the maxmium of two numbers.

    The two values must be integers.'''
    # convert to integers, if possible
    x = int(x)
    y = int(y)

    if x > y:
        print(x, "is maxmium")
    else:
        print(y, "is maxmium")


print_max(3, 5)
print(print_max.__doc__)
