from zad1ktesty import runtests

def roznica( S ):
    #Tutaj proszę wpisać własną implementację
    F = [-1 for _ in range(len(S))]
    if S[0] == '0':
        F[0] = 1
    n = len(S)
    start = 0
    while start < n and S[start] != '0':
        start += 1

    if start < n:   F[start] = 1

    for i in range(start+1,n):
        F[i] = F[i-1]
        if S[i] == '0':
            F[i] += 1
        else:
            F[i] -= 1
        if F[i] < 0:
            F[i] = 0


    return max(F)
runtests ( roznica )
