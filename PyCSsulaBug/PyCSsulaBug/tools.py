#-*- coding: utf-8 -*-

class Queue:

    def __init__(self):
        self.m_list = []
    
    def enqueue(self, item):
        self.m_list.append(item)

    def dequeue(self):
        item = self.m_list[0]
        self.m_list = self.m_list[1:]
        return item

    def head(self):
        return self.m_list[0]

    def isEmpty(self):
        return len(self.m_list) == 0