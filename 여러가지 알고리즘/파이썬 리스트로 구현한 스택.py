def push(list, item):
    list.append(item)

def pop(list):
    if len(list) > 0:
        temp = list[-1]
        del list[-1]
        return temp

def peek(list):
    if len(list) > 0:
        return list[-1]

stack = []

print(peek(stack))
push(stack, 5)
push(stack, 3)
print(peek(stack))
print(pop(stack))
print(peek(stack))
print(pop(stack))
print(peek(stack))

