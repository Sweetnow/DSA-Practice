#!/usr/bin/env python3
# -*- coding:UTF-8 -*-

s = '503，087，512，061，908，170，897，275，653，426'


result = []


def insert_sort(lst):
    l = []
    sort_num = 0
    for num in lst:
        i = 0
        while i < len(l) and l[i] < num:
            i += 1
        l.insert(i, num)
        sort_num += 1
        print(l+lst[sort_num:])


def quick_sort(lst, start, end):
    if end <= start+1:
        return None
    pivot_index = start
    low = start+1
    high = end - 1
    while low < high:
        while low < high and lst[high] >= lst[pivot_index]:
            high -= 1
        lst[high], lst[pivot_index] = lst[pivot_index], lst[high]
        result.append(str(lst))
        pivot_index = high
        while low < high and lst[low] <= lst[pivot_index]:
            low += 1
        lst[low], lst[pivot_index] = lst[pivot_index], lst[low]
        result.append(str(lst))
        pivot_index = low
    quick_sort(lst, start, low)
    quick_sort(lst, low + 1, end)
    return None


def main():
    nums = [int(num) for num in s.split('，')]
    print(nums)
    quick_sort(nums, 0, len(nums))
    i = 0
    while i < len(result)-1:
        if result[i] == result[i + 1]:
            result.remove(result[i + 1])
        else:
            i += 1
    for string in result:
        print(string)


if __name__ == '__main__':
    main()
