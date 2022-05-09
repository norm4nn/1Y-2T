from zad1ktesty import runtests


def ksuma(T, k):
    n = len(T)
    F = [0 for _ in range(n)]
    for i in range(k):
        F[i] = T[i]
    for i in range(k,n):
        F[i] = T[i]
        F[i] += min(F[i-k:i])

    print(k,F[n-k:n],min(F[n-k:n]))

    return min(F[n - k :n])

runtests(ksuma)
