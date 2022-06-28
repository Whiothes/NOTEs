while True:
    s = input('Enter something:')
    if s == 'quit':
        break
    if len(s) < 3:
        print('Too samll')
        continue
    print('Input is of sufficient length')
