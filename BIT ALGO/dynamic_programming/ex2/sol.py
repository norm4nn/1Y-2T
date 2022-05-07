from zad1ktesty import runtests

def palindrom( S ):
    #Tutaj proszę wpisać własną implementację
    n = len(S)
    F = [[0 for __ in range(n)] for _ in range(n)]
    for i in range(n):
        F[i][i] = 1
    
    for i in range(1,n):
        for j in range(0,n-i):
            if (j+1 > i+j-1 or F[j+1][i+j-1] > 0) and S[i+j] == S[j]:
                F[j][i+j] = i + 1
            # for w in range(n):
            #     print(F[w])
            # print()
    # L = []
    # for i in range(n):
    #     L.append(max(F[i]))
    # print(max(L))

    for i in range(n-1,0,-1):
        for j in range(n-i-1,-1,-1):
            if F[j][i+j] != 0:
                return S[j:i+j+1]

    return ""

runtests ( palindrom )

#palindrom("a")
