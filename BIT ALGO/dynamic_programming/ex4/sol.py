from zad1ktesty import runtests

def falisz ( T ):
    #Tutaj proszę wpisać własną implementację
    n = len(T)
    F = [[0 for __ in range(n)] for _ in range(n)]

    for i in range(1,n):
        F[i][0] = F[i-1][0] + T[i][0]
        F[0][i] = F[0][i-1] + T[0][i]

    for i in range(1,n):
        for j in range(i+1):
            if i-j !=0 and j != 0:
                F[j][i-j] = T[j][i-j]
                F[j][i-j] += min(F[j-1][i-j],F[j][i-j-1])

    for i in range(n-1,0,-1):
        for j in range(i):
            F[n-1-j][j + n-i] = T[n-1-j][j + n-i]
            F[n-1-j][j + n-i] += min(F[n-1-j- 1][j + n-i], F[n-1-j][j + n-i - 1])


    return F[n-1][n-1]

runtests ( falisz )
