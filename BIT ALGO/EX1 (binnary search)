import random


# def NWD(a,b):
#     while b:
#         a,b = b, a%b
#     return a

def injectionSort(M):

    for i in range(1,len(M)):
        for j in range(i,0,-1):
            if M[j] <= M[j-1]:
                M[j],M[j-1] = M[j-1],M[j]
            else:
                break

def binarySearch(T,val):
    l = 0
    r = len(T) - 1
    while l <= r:
        mean = (r+l)//2
        if T[mean] > val:
            r = mean - 1
        if T[mean] < val:
            l = mean + 1
        if T[mean] == val:
            return True
    return False


def any_both(N,M):#M << N
    #sort m
    bothInclude = []
    pass
    injectionSort(M)
    #szukanie polowkowe w m liczby n
    for val in N:
        if binarySearch(M,val):
            bothInclude.append(val)

    return bothInclude

#m << n
N_range = 100
M_range = 10
N = [random.randint(0,50000) for _ in range(N_range)]
M = [random.randint(0,50000) for _ in range(M_range)]
print(M)
print(any_both(N,M))
