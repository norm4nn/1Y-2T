import math

from zad1ktesty import runtests

def f(T,i,sum1,sum2,F):
    if i == len(T):
        F[i-1] = abs(sum1-sum2)
        return F[i-1]
    if F[i] != -1:
        return F[i]
    else:
        to1 = f(T,i+1,sum1+T[i],sum2,F)
        to2 = f(T,i+1,sum1,sum2+T[i],F)
        return min(to1,to2)
def kontenerowiec(T):
    #Tutaj proszę wpisać własną implementację
    n = len(T)
    S = 0
    for i in range(len(T)):
        S += T[i]
    F = [[0 for _ in range(S + 1)] for __ in range(n)]


    F[0][T[0]] = 1
    for i in range(1,n):
        for j in  range(S+1):
            if F[i][j] == 0:
                F[i][j] = F[i-1][j]
            if F[i-1][j] != 0:
                F[i][j+T[i]] = 1
    minimum = S
    for i in range(S+1):
        if F[n-1][i] == 1 and abs((S-i) - i) < minimum:
            minimum = abs((S - i) - i)
    return minimum


    #result =f(T,0,0,0,F)
    #return result


runtests ( kontenerowiec )
