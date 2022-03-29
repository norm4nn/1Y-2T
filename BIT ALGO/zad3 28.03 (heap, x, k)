import random
T = [random.randint(1,50) for _ in range(10)]
def left(i):
    return 2*i + 1

def right(i):
    return 2*i + 2

def heapifyMIN(T,n,k):
    min0 = k
    l = left(k)
    r = right(k)

    if l < n and T[min0] > T[l]:
        min0 = l
    if r < n and T[min0] > T[r]:
        min0 = r
    if min0 != k:
        T[k],T[min0] = T[min0],T[k]
        heapifyMIN(T,n,min0)

def buildMINHeap(T):
    for i in range(len(T)//2,-1,-1):
        heapifyMIN(T,len(T),i)


def func(T,x,k):
    howMany = 0
    n = len(T)
    if T[0] >= x: return True
    stack = [0]
    while stack:
        tmp = stack.pop(-1)
        howMany += 1
        if howMany == k:    return False

        if left(tmp) < n and T[left(tmp)] < x: stack.append(left(tmp))
        if right(tmp) < n and T[right(tmp)] < x: stack.append(right(tmp))
    return True



print(T)

buildMINHeap(T)
print(T)

print(func(T,10,1))
