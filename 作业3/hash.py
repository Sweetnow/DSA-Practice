#!/usr/bin/env python3
# -*- coding:UTF-8 -*-

M = 13
sin = '25, 37, 52, 43, 84, 99, 15, 70, 11'

def main():
    raw = [int(num) for num in sin.split(', ')]
    good = [(num, num % M) for num in raw]
    array = [0] * M
    rush = [0] * M
    for (r, h) in good:
        i = 0
        while array[(h + i) % M] != 0:
            rush[(h + i) % M] += 1
            i += 1
        else:
            array[(h + i) % M] = r
    print(good)
    print(','.join(map(str, array)) + '\n' + ','.join(map(str, rush)) + '\n')
    # finding length on average
    count = 0
    for (r, h) in good:
        i = 0
        while array[(h + i) % M] != r:
            i += 1
        else:
            count += i + 1
            print(str(i+1)+'+',end='')
    print('finding length on average is %f' % (count / len(raw)))
    



if __name__ == '__main__':
    main()
