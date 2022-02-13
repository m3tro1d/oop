with open('heavy.txt', 'w') as f:
    for i in range(10000000):
        f.write('A')
    f.write('\n')
