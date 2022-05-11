from zad1ktesty import runtests

def f(N,i,L):
    if N == 0:
        return L
    if i*i > N:
        L = []
        return

    N -= i
    L.append(i)
    A = f(N-i*i,)






def dywany ( N ):
    #Tutaj proszę wpisać własną implementację
    F = [[] for _ in range(N+1)]
    a = 1
    print(N)
    for i in  range(1,N+1):
        j = 1
        F[i] = F[i-1].copy()
        F[i].append(1)
        while i - (j**2) >= 0:

            if len(F[i-(j**2)]) < len(F[i]):
                F[i] = F[i-(j**2)].copy()
                F[i].append(j)
                # if (a+1)**2 <= i:
                #     F[i] = F[i-((a+1)**2)].copy()
                #     F[i].append(a+1)
                #     a += 1
            j += 1

    return F[N]


runtests( dywany )

print(dywany(18))
