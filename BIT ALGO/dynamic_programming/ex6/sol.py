from zad1ktesty import runtests


def divide(S,i,sum):
    if i == len(S) - 1:
        return sum


def haslo ( S ):
    n = len(S)
    # if ord(S[0]) != 48:
    #     result += 1
    F = [0 for _ in range(n)]
    if int(S[0]):
        F[0] = 1

    for i in range(1,n):
        F[i] = F[i-1]
        if int(S[i])== 0:
            if int(S[i-1]) != 1 and int(S[i-1]) != 2:
                F[i] = 0
                break
            elif i > 1:
                F[i] = F[i-2]
            else:
                F[i] = F[0]
        if int(S[i-1:i+1]) <= 26 and int(S[i-1:i+1]) >= 10 and int(S[i]) != 0 :
            if i > 1:
                F[i] += F[i-2]
            else:
                F[i] += 1





    print(S)
    return F[n-1]

runtests ( haslo )
