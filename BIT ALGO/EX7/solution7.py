import random
A = [random.randint(0,20) for _ in range(4)]
B = [random.randint(0,20) for _ in range(4)]
C = [random.randint(0,20) for _ in range(4)]

def partition(T,l,r):
    x = T[r]
    j = l -1
    for i in range(l,r):
        if T[i] <= x:
            j += 1
            T[i], T[j] = T[j], T[i]
    j += 1
    T[j],T[r] = T[r],T[j]
    return j
def partition2(T,l,r):
    x = T[r]
    j = l -1
    for i in range(l,r):
        if T[i] >= x:
            j += 1
            T[i], T[j] = T[j], T[i]
    j += 1
    T[j],T[r] = T[r],T[j]
    return j

def qs(T,l,r):
    if l < r:
        q = partition(T,l,r)
        qs(T,l,q-1)
        qs(T,q+1,r)

def qs2(T,l,r):
    if l < r:
        q = partition2(T,l,r)
        qs(T,l,q-1)
        qs(T,l,q+1)

def if_sumFunc(A,B,C):#if exist A + B = C
    qs(A,0,len(A) - 1)
    qs(B,0,len(B) - 1)

    for Cval in C:
        flag = False
        Apoint = 0
        Bpoint = len(B) - 1
        sum0 = A[Apoint] + B[Bpoint]
        while sum0 != Cval:
            while sum0 < Cval:
                Apoint += 1
                if Apoint >= len(A):
                    flag = True
                    break
                sum0 = A[Apoint] + B[Bpoint]
            while sum0 > Cval:
                Bpoint -= 1
                if Bpoint < 0 :
                    flag = True
                    break
                sum0 = A[Apoint] + B[Bpoint]
            if flag:
                break
        else:
            return True
    return False

print(if_sumFunc(A,B,C))
print(A)
print(B)
print(C)

