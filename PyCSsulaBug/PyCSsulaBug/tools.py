#-*- coding: utf-8 -*-

class Queue:

    def __init__(self):
        self._list = []
    
    def enqueue(self, item):
        self._list.append(item)

    def dequeue(self):
        item = self._list[0]
        self._list = self._list[1:]
        return item

    def head(self):
        return self._list[0]

    def isEmpty(self):
        return len(self._list) == 0