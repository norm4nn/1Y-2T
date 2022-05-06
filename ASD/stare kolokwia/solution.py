from zad1testy import runtests

def whereIN(n,k):#k-ty element njamniejszy iterowane od 0
    count = n ** 2 - n
    count //= 2
    if k < count:
        row = 1
        col = 0
        while k > 0:
            col += 1
            if row == col:
                if row < n - 1:
                    row += 1
                    col = 0
            k -= 1
        return (row,col)
    return(k-count + 1,k - count + 1)

def partition(T,l,r):
    n = len(T)
    x = T[r//n][r%n]
    j = l -1

    for i in range(l,r):
        if T[i//n][i%n] <= x:
            j += 1
            T[i//n][i%n],T[j//n][j%n] = T[j//n][j%n],T[i//n][i%n]
            #print(T[i][col],"<->",T[j][col])
    j += 1
    T[j//n][j%n],T[r//n][r%n] = T[r//n][r%n],T[j//n][j%n]
    return j

def quickSelect(T,k,l,r):#T = N x N
    if l < r:
        q = partition(T,l,r)
        if k < q:
            quickSelect(T,k,l,q-1)
        elif k > q:
            quickSelect(T,k,q+1,r)
        else:
            return



def Median(T):
    n = len(T)
    count = n**2 - n
    count //= 2

    for i in range(n):
        quickSelect(T,count+i,0,n*n-1)
        #print(T[(count+i)//n][(count+i)%n])
    lim = T[count//n][count%n]
    for i in range(n):
        T[(count+i)//n][(count+i)%n],T[i][i] = T[i][i],T[(count+i)//n][(count+i)%n]
    # for lis in T:
    #      print(lis)
    wD = 1
    kD = 0
    i = 0
    #for i in range(n*n):
    while i < n*n:
        w = i//n
        k = i%n
        if  k > w and T[w][k] <= lim and wD <= n - 1:
            #print(T[w][k], " <=> ", T[wD][kD])
            T[w][k],T[wD][kD] = T[wD][kD],T[w][k]
            kD += 1
            if kD == wD and wD < n - 1:
                wD += 1
                kD = 0
            elif kD == wD and wD == n - 1:
                wD = 1
                kD = 0
            i -= 1
        i += 1

    return T

runtests( Median )
