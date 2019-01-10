#!/usr/bin/env python3
# -*- coding:UTF-8 -*-


class node:
    def __init__(self, data, left=None, right=None):
        self.data = data
        self.left = left
        self.right = right
        return None


class tree:
    def __init__(self):
        self.root = None
        return None
    def insert(self, data):
        if self.root is None:
            self.root=node(data)
        else:
            parent=self.root
            now = self.root.left if data < self.root.data else self.root.right 
            while now is not None:
                parent=now
                now = now.left if data < now.data else now.right
            if data < parent.data:
                parent.left = node(data)
            else:
                parent.right = node(data)
        return self

def main():
    s = input()
    t = tree()
    for c in s.split():
        t.insert(c)
    str(t)

if __name__ == '__main__':
    main()

