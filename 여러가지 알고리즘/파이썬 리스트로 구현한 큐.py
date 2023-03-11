#add remove print

def add(list, item):
    list.append(item)

def remove(list):
    if len(list) > 0:
        temp = list[0]
        del list[0]
        return temp
    
def printQ(list):
    for i in list:
        print(i)
    print('\n')


q = []
add(q, 1)
add(q, 2)
add(q, 3)
printQ(q)
remove(q)
remove(q)
printQ(q)