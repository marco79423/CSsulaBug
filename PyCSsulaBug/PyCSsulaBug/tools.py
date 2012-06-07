#-*- coding: cp950 -*-
class Queue:

    def __init__(self):
        self.qList = []
    
    def enqueue(self, item):
        self.qList.append(item)

    def dequeue(self, item):
        item = self.qList[0]
        self.qList = self.qList[1:]
        return item

    def top(self):
        return qList[0]

    def isEmpty(self):
        return len(self.qList) == 0