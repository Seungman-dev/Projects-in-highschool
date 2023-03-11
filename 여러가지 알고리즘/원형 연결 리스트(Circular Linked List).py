

class CircularLinekdList:
    class Node:
        def __init__(self, item, next):
            self.item = item
            self.next = next
    def __init__(self):
        self.last = None
        self.size = 0
    def size(self): return self.size
    def is_empty(self): return self.size == 0
    def insertFront(self, item):
        if self.size == 0:
            self.last = self.Node(item, None)
            self.last.next = self.last
        else:
            self.last.next = self.Node(item, self.last.next)
        self.size += 1
    def deleteFront(self):
        if(self.size == 1):
            self.last = None
        else:
            self.last.next = self.last.next.next
        self.size -= 1
    def printList(self, num):
        if(self.size == 0):
            print("원형 리스트가 비어있습니다.")
        else:
            iter = self.last
            for i in range(num):
                iter = iter.next
                if(i == num - 1):
                    print(iter.item)
                else:
                    print(f"{iter.item} -> ", end = '')


test = CircularLinekdList()
test.insertFront(4)
test.insertFront(3)
test.insertFront(2)
test.insertFront(1)
test.printList(10)
test.deleteFront()
test.deleteFront()
test.deleteFront()
test.printList(10)
test.deleteFront()
test.printList(10)
