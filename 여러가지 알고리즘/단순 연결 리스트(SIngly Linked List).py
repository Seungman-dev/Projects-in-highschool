class Slist:
    
    class Node:
        def __init__(self, item, next):
            self.item = item
            self.next = next

    def __init__(self):
        self.head = None
        self.size = 0

    def size(self): return self.size
    def is_empty(self): self.size == 0

    def insert_front(self, item):
        if self.is_empty():
            self.head = self.Node(item, None)
        else:
            self.head = self.Node(item, self.head)
        self.size += 1
    
    def insert_after(self, item, p):
        p.next = self.Node(item, p.next)
        self.size += 1

    def delete_front(self):
        if self.is_empty():
            raise EmptyError("Underflow")
        else:
            self.head = self.head.next
            self.size -= 1

    def delete_after(self, p):
        if self.is_empty():
            raise EmptyError("Underflow")
        else:
            p.next = p.next.next
            self.size -= 1
    #p가 있는지 확인하는 부분 없고, p의 다음 노드가 없는 경우 고려 안함

    def search(self, target):
        temp = self.head
        for i in range(self.size):
            if temp.item == target: return i
            temp = temp.next
        return None
    
    def print_list(self):
        temp = self.head
        for i in range(self.size):
            if temp.next == None:
                print(temp.item)
            else:
                print(temp.item, " -> ", end = '')
            temp = temp.next
        

class EmptyError(Exception):
    pass

s = Slist()
s.insert_front("orange")
s.insert_front("apple")
s.insert_after("cherry", s.head.next)
s.insert_front("pear")
s.print_list()
print("cherry는 %d번째" %s.search("cherry"))
print(f"kiwi는 {s.search('kiwi')}번째")
print("배 다음 노드 삭제 후:\t\t", end = '')
s.delete_after(s.head)
s.print_list()
print("첫 노드 삭제 후:\t\t", end = '')
s.delete_front()
s.print_list()
print("첫 노드로 망고, 딸기 삽입 후:\t", end = '')
s.insert_front("mango")
s.insert_front("strawberry")
s.print_list()
s.delete_after(s.head.next.next)
print("오렌지 다음 노드 삭제 후:\t", end = '')
s.print_list()
