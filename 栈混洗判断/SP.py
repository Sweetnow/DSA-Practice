#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 栈混洗判断
from copy import *
def main():
    s=input("输入待判断的序列(bottom->top):")
    list_SP=[int(x) for x in s.split()]
    list_RAW=copy(list_SP)
    list_RAW.sort()
    list_RAW.reverse()
    stack_tmp=[]
    print('RAW',list_RAW)
    print('after SP',list_SP)
    
    for i in range(len(list_SP)):
        while(list_SP[i] not in stack_tmp and len(list_RAW)>0):
            stack_tmp.append(list_RAW.pop())
            print('push')
        if(list_SP[i] in stack_tmp and list_SP[i] == stack_tmp[-1]):
            stack_tmp.pop()
            print('pop')
        else:
            print('false')
            return
    print('true')
    return
        
if __name__=='__main__':
    main()
